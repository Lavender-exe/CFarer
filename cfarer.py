#!/usr/bin/env python3
"""
CFarer - Learn C through small exercises
Inspired by rustlings (https://github.com/rust-lang/rustlings)

Usage:
    python cfarer.py [--track NAME] [command] [args]

Commands:
    watch  [--track NAME]    Start watch mode (default command)
    list   [--track NAME]    List exercises and progress
    hint   [--track NAME]    Show hint for current exercise
    run    [--track NAME]    Compile/run current exercise once
    reset  [--track NAME]    Show how to restore current exercise
    goto N [--track NAME]    Jump to exercise number N
    tracks                   List all available tracks

Tracks (exercise directories):
    c23          exercises/           C language fundamentals + C23
    maldev       exercises_maldev/    Malware development (Windows, authorized use)
    winternals   exercises_winternals/ Windows internals

Watch mode commands (type + Enter):
    hint         Show progressive hints
    list         List exercises with progress
    next         Skip to next exercise
    goto N       Jump to exercise N
    track NAME   Switch to a different track
    quit         Exit
"""

import os
import sys
import json
import time
import subprocess
import shutil
import platform
import threading
import queue
from pathlib import Path

# ─── Root ──────────────────────────────────────────────────────────────────────

ROOT_DIR      = Path(__file__).parent.resolve()
DONE_MARKER   = "// I AM NOT DONE"
POLL_INTERVAL = 0.5
RUN_TIMEOUT   = 10

# ─── Colors ────────────────────────────────────────────────────────────────────

if platform.system() == "Windows":
    os.system("")

class C:
    GREEN  = "\033[92m"
    RED    = "\033[91m"
    YELLOW = "\033[93m"
    BLUE   = "\033[94m"
    CYAN   = "\033[96m"
    MAGENTA= "\033[95m"
    BOLD   = "\033[1m"
    DIM    = "\033[2m"
    RESET  = "\033[0m"

def clr(text, *codes):
    return "".join(codes) + str(text) + C.RESET


# ─── Track discovery ───────────────────────────────────────────────────────────

# Track metadata: display name, color, completion message
TRACK_META = {
    "c23":        ("C23 Fundamentals",    C.CYAN,    "You've learned C23!"),
    "maldev":     ("Malware Development", C.RED,     "Maldev track complete - authorized research only!"),
    "winternals": ("Windows Internals",   C.MAGENTA, "Windows Internals track complete!"),
    "linux":      ("Linux Internals",     C.GREEN,   "Linux Internals track complete!"),
    "redteam":    ("Red Team Ops",        C.RED,     "Red Team track complete - authorized engagements only!"),
}

def discover_tracks() -> dict:
    """Return {track_name: Path} for all exercises* dirs present on disk."""
    tracks = {}
    default = ROOT_DIR / "exercises"
    if default.exists():
        tracks["c23"] = default
    for d in sorted(ROOT_DIR.iterdir()):
        if d.is_dir() and d.name.startswith("exercises_"):
            name = d.name[len("exercises_"):]
            tracks[name] = d
    return tracks

def track_dir(track_name: str) -> Path:
    tracks = discover_tracks()
    if track_name not in tracks:
        print(clr(f"Unknown track: {track_name!r}", C.RED))
        print(f"Available: {', '.join(tracks)}")
        sys.exit(1)
    return tracks[track_name]

def state_file(track_name: str) -> Path:
    return ROOT_DIR / f".cfarer_state_{track_name}.json"

def track_label(track_name: str) -> str:
    meta = TRACK_META.get(track_name)
    return meta[0] if meta else track_name.upper()

def track_color(track_name: str) -> str:
    meta = TRACK_META.get(track_name)
    return meta[1] if meta else C.CYAN

def track_done_msg(track_name: str) -> str:
    meta = TRACK_META.get(track_name)
    return meta[2] if meta else "Track complete!"


# ─── Exercise discovery ────────────────────────────────────────────────────────

def get_exercises(track_name: str) -> list:
    return sorted(track_dir(track_name).glob("*.c"))


# ─── State ─────────────────────────────────────────────────────────────────────

def load_state(track_name: str) -> dict:
    sf = state_file(track_name)
    if sf.exists():
        try:
            return json.loads(sf.read_text(encoding="utf-8"))
        except Exception:
            pass
    return {"current_index": 0, "completed": []}

def save_state(track_name: str, state: dict):
    state_file(track_name).write_text(json.dumps(state, indent=2), encoding="utf-8")

def current_exercise(track_name: str, state: dict):
    exercises = get_exercises(track_name)
    if not exercises:
        return None
    idx = min(state.get("current_index", 0), len(exercises) - 1)
    return exercises[idx]


# ─── Compiler ──────────────────────────────────────────────────────────────────

def find_compiler() -> str | None:
    order = ["clang", "gcc", "cl"] if platform.system() == "Windows" else ["clang", "gcc", "cc"]
    for name in order:
        if shutil.which(name):
            return name
    return None

def build_compile_cmd(compiler: str, src: Path, out: Path, track_name: str) -> list:
    src_s, out_s = str(src), str(out)
    is_win_track   = track_name in ("maldev", "winternals")
    is_linux_track = track_name == "linux"

    if compiler == "cl":
        cmd = ["cl", "/nologo", "/std:c11", "/W3", f"/Fe:{out_s}", src_s]
        if is_win_track:
            cmd += ["/link", "kernel32.lib", "advapi32.lib", "user32.lib",
                    "ntdll.lib", "ws2_32.lib"]
        if is_linux_track:
            print(clr("WARNING: linux track exercises require gcc on Linux.", C.YELLOW))
        return cmd
    else:
        std = "c11" if (is_win_track or is_linux_track) else "c2x"
        cmd = [compiler, f"-std={std}", "-Wall", "-Wextra", "-o", out_s, src_s]
        if is_linux_track:
            cmd += ["-lrt", "-lpthread"]
        elif platform.system() != "Windows":
            cmd.append("-lm")
        return cmd


# ─── Compile + run ─────────────────────────────────────────────────────────────

def compile_and_run(c_file: Path, compiler: str, track_name: str):
    """Returns (ok, compile_output, run_output)."""
    ext = ".exe" if platform.system() == "Windows" else ".out"
    out = c_file.with_suffix(ext)

    cmd = build_compile_cmd(compiler, c_file, out, track_name)
    cp  = subprocess.run(cmd, capture_output=True, text=True)
    compile_out = (cp.stdout + cp.stderr).strip()

    if cp.returncode != 0:
        return False, compile_out, ""

    try:
        rp = subprocess.run([str(out)], capture_output=True, text=True, timeout=RUN_TIMEOUT)
        run_out = (rp.stdout + rp.stderr).strip()
        ok = (rp.returncode == 0)
        if rp.returncode != 0 and not run_out:
            run_out = f"[process exited with code {rp.returncode}]"
        return ok, compile_out, run_out
    except subprocess.TimeoutExpired:
        return False, compile_out, f"[ERROR: program exceeded {RUN_TIMEOUT}s timeout]"
    finally:
        try:
            out.unlink(missing_ok=True)
        except Exception:
            pass


# ─── Hints ─────────────────────────────────────────────────────────────────────

def load_hint(c_file: Path) -> str:
    hp = c_file.with_suffix(".hint")
    return hp.read_text(encoding="utf-8").strip() if hp.exists() else "(No hint file for this exercise.)"


# ─── Display ───────────────────────────────────────────────────────────────────

def clear_screen():
    os.system("cls" if platform.system() == "Windows" else "clear")

def make_banner(track_name: str) -> str:
    col  = track_color(track_name)
    lbl  = track_label(track_name)
    line = f"CFarer  [{lbl}]"
    pad  = max(0, 44 - len(line))
    lpad = pad // 2
    rpad = pad - lpad
    return (
        f"\n{col}{C.BOLD}"
        f"╔═══════════════════════════════════════════════╗\n"
        f"║{' ' * lpad}{line}{' ' * rpad}   ║\n"
        f"║  Edit exercise files  ·  Remove I AM NOT DONE ║\n"
        f"╚═══════════════════════════════════════════════╝{C.RESET}\n"
    )

def print_banner(track_name: str):
    print(make_banner(track_name))

def divider(label="", width=50):
    if label:
        pad = (width - len(label) - 2) // 2
        print(clr("─" * pad + f" {label} " + "─" * pad, C.DIM))
    else:
        print(clr("─" * width, C.DIM))

def print_status(ex_name, idx, total):
    print(f"  Exercise {clr(idx+1, C.BOLD)}/{total}  ·  {clr(ex_name, C.BOLD)}")
    print()

def print_success_box(run_output):
    print(clr("  ✓  Compiled and ran successfully!", C.GREEN, C.BOLD))
    print()
    if run_output:
        divider("Output")
        print(run_output)
        print()

def print_not_done_box(run_output):
    print(clr("  ◑  Compiled OK - remove '// I AM NOT DONE' to advance", C.YELLOW, C.BOLD))
    print()
    if run_output:
        divider("Output")
        print(run_output)
        print()

def print_failure_box(compile_output):
    print(clr("  ✗  Compilation failed", C.RED, C.BOLD))
    print()
    divider("Errors")
    print(compile_output)
    print()
    print(clr("  → type 'hint' + Enter for a hint", C.YELLOW))
    print()

def print_runtime_failure_box(run_output):
    print(clr("  ✗  Program crashed or assertion failed", C.RED, C.BOLD))
    print()
    divider("Output")
    print(run_output)
    print()
    print(clr("  → type 'hint' + Enter for a hint", C.YELLOW))
    print()


# ─── Inline command handler ────────────────────────────────────────────────────

def _handle_inline_cmd(cmd: str, track_name: str, state: dict, exercises: list) -> str:
    """Handle a typed command during watch mode. Returns new track_name (may change)."""
    if cmd in ("q", "quit", "exit"):
        print("\nGoodbye!")
        sys.exit(0)

    elif cmd == "hint":
        ex = current_exercise(track_name, state)
        if ex:
            print()
            divider("Hint")
            print(load_hint(ex))
            print()

    elif cmd == "list":
        print()
        _print_list(track_name, state, exercises)
        print()

    elif cmd.startswith("goto "):
        parts = cmd.split()
        try:
            n = int(parts[1]) - 1
            if 0 <= n < len(exercises):
                state["current_index"] = n
                save_state(track_name, state)
                print(clr(f"  Jumped to exercise {n+1}: {exercises[n].name}", C.CYAN))
            else:
                print(clr(f"  Invalid exercise number (1–{len(exercises)})", C.RED))
        except (ValueError, IndexError):
            print(clr("  Usage: goto <number>", C.YELLOW))

    elif cmd == "next":
        idx = state.get("current_index", 0)
        if idx + 1 < len(exercises):
            state["current_index"] = idx + 1
            save_state(track_name, state)
            print(clr(f"  Skipped to: {exercises[idx+1].name}", C.YELLOW))
        else:
            print(clr("  Already at last exercise!", C.YELLOW))

    elif cmd.startswith("track "):
        parts = cmd.split(None, 1)
        new_track = parts[1].strip() if len(parts) > 1 else ""
        available = discover_tracks()
        if new_track in available:
            print(clr(f"  Switching to track: {new_track}", C.CYAN))
            return new_track   # signal caller to switch
        else:
            print(clr(f"  Unknown track: {new_track!r}  -  available: {', '.join(available)}", C.RED))

    elif cmd == "tracks":
        _print_tracks()

    elif cmd == "":
        pass

    else:
        print(clr(f"  Unknown: {cmd!r}  (hint · list · next · goto N · track NAME · quit)", C.DIM))

    return track_name   # unchanged


def _print_list(track_name: str, state: dict, exercises: list):
    completed   = state.get("completed", [])
    current_idx = state.get("current_index", 0)
    col         = track_color(track_name)
    print(f"  Track: {clr(track_label(track_name), col, C.BOLD)}  "
          f"Progress: {clr(len(completed), C.GREEN)}/{clr(len(exercises), C.CYAN)}")
    print()
    for i, ex in enumerate(exercises):
        if ex.name in completed:
            marker = clr("✓", C.GREEN)
        elif i == current_idx:
            marker = clr("→", C.YELLOW, C.BOLD)
        else:
            marker = clr("○", C.DIM)
        num = clr(f"{i+1:>2}.", C.DIM)
        print(f"    {num} {marker}  {ex.name}")


def _print_tracks():
    tracks = discover_tracks()
    print()
    print(f"  {clr('Available tracks:', C.BOLD)}")
    print()
    for name, path in tracks.items():
        exs  = sorted(path.glob("*.c"))
        st   = load_state(name)
        done = len(st.get("completed", []))
        col  = track_color(name)
        lbl  = track_label(name)
        print(f"    {clr(f'{name:<12}', col, C.BOLD)}  {lbl:<24}  "
              f"{clr(done, C.GREEN)}/{clr(len(exs), C.CYAN)} done  "
              f"{clr(str(path.relative_to(ROOT_DIR)), C.DIM)}")
    print()


# ─── watch ─────────────────────────────────────────────────────────────────────

def cmd_watch(track_name: str):
    compiler = find_compiler()
    if not compiler:
        print(clr("ERROR: No C compiler found in PATH!", C.RED, C.BOLD))
        print("Install:  gcc  |  clang  |  (Windows: cl via MSVC Build Tools)")
        sys.exit(1)

    # mutable so inner fn can reassign via return value
    ctx = {"track": track_name}

    def run_watch():
        tn        = ctx["track"]
        state     = load_state(tn)
        exercises = get_exercises(tn)

        if not exercises:
            print(clr(f"No exercises found in {track_dir(tn)}", C.RED))
            sys.exit(1)

        clear_screen()
        print_banner(tn)
        print(f"  Compiler : {clr(compiler, C.CYAN)}")
        print(f"  Exercises: {clr(len(exercises), C.CYAN)}")
        print()
        print(f"  {clr('Commands:', C.BOLD)}  hint · list · next · goto N · track NAME · tracks · quit")
        print()

        input_q    = queue.Queue()
        last_mtime = [None]
        last_ex    = [None]

        def _reader():
            while True:
                try:
                    line = sys.stdin.readline()
                    if not line:
                        break
                    input_q.put(line.strip().lower())
                except Exception:
                    break

        threading.Thread(target=_reader, daemon=True).start()

        while True:
            # ── process commands ──────────────────────────────────────────────
            try:
                while True:
                    cmd = input_q.get_nowait()
                    new_tn = _handle_inline_cmd(cmd, tn, state, exercises)
                    if new_tn != tn:
                        ctx["track"] = new_tn
                        return   # restart with new track
                    last_mtime[0] = None
            except queue.Empty:
                pass

            # ── check completion ──────────────────────────────────────────────
            ex = current_exercise(tn, state)
            if ex is None:
                print(clr(f"\n  ALL EXERCISES COMPLETE!  {track_done_msg(tn)}\n",
                          track_color(tn), C.BOLD))
                break

            # ── poll for changes ──────────────────────────────────────────────
            try:
                mtime = ex.stat().st_mtime
            except FileNotFoundError:
                time.sleep(POLL_INTERVAL)
                continue

            if ex == last_ex[0] and mtime == last_mtime[0]:
                time.sleep(POLL_INTERVAL)
                continue

            last_ex[0]    = ex
            last_mtime[0] = mtime
            idx = state.get("current_index", 0)

            # ── evaluate ──────────────────────────────────────────────────────
            clear_screen()
            print_banner(tn)
            print_status(ex.name, idx, len(exercises))

            content    = ex.read_text(encoding="utf-8")
            has_marker = DONE_MARKER in content
            ok, cout, rout = compile_and_run(ex, compiler, tn)

            if not ok and not rout:
                print_failure_box(cout)
            elif not ok and rout:
                print_runtime_failure_box(rout)
            elif has_marker:
                print_not_done_box(rout)
            else:
                print_success_box(rout)
                completed = state.get("completed", [])
                if ex.name not in completed:
                    completed.append(ex.name)
                    state["completed"] = completed

                next_idx = idx + 1
                if next_idx < len(exercises):
                    state["current_index"] = next_idx
                    save_state(tn, state)
                    print(clr(f"  → Moving to: {exercises[next_idx].name}", C.GREEN))
                    print()
                    time.sleep(2.5)
                    last_mtime[0] = None
                else:
                    save_state(tn, state)
                    print(clr(f"  ALL EXERCISES COMPLETE!  {track_done_msg(tn)}",
                              track_color(tn), C.BOLD))
                    print()
                    sys.exit(0)

            time.sleep(POLL_INTERVAL)

    # outer loop restarts watch when track switches
    while True:
        run_watch()


# ─── Standalone commands ───────────────────────────────────────────────────────

def cmd_list(track_name: str):
    state     = load_state(track_name)
    exercises = get_exercises(track_name)
    print_banner(track_name)
    _print_list(track_name, state, exercises)
    print()

def cmd_hint(track_name: str):
    state = load_state(track_name)
    ex    = current_exercise(track_name, state)
    if ex is None:
        print("No exercises found.")
        return
    print()
    print(clr(f"Hint for {ex.name}:", C.YELLOW, C.BOLD))
    divider()
    print(load_hint(ex))
    print()

def cmd_run(track_name: str):
    compiler = find_compiler()
    if not compiler:
        print(clr("No C compiler found in PATH!", C.RED))
        sys.exit(1)
    state     = load_state(track_name)
    ex        = current_exercise(track_name, state)
    if ex is None:
        print("No exercises found.")
        return
    idx       = state.get("current_index", 0)
    exercises = get_exercises(track_name)
    print_banner(track_name)
    print_status(ex.name, idx, len(exercises))
    ok, cout, rout = compile_and_run(ex, compiler, track_name)
    if not ok and not rout:
        print_failure_box(cout)
    elif not ok:
        print_runtime_failure_box(rout)
    else:
        content = ex.read_text(encoding="utf-8")
        if DONE_MARKER in content:
            print_not_done_box(rout)
        else:
            print_success_box(rout)

def cmd_reset(track_name: str):
    state = load_state(track_name)
    ex    = current_exercise(track_name, state)
    if ex is None:
        print("No exercises found.")
        return
    rel = ex.relative_to(ROOT_DIR)
    print()
    print(clr("To restore the original exercise:", C.YELLOW, C.BOLD))
    print(f"  git checkout {rel}")
    print()

def cmd_goto(n: int, track_name: str):
    exercises = get_exercises(track_name)
    idx       = n - 1
    if not (0 <= idx < len(exercises)):
        print(clr(f"Exercise {n} not found (valid: 1–{len(exercises)})", C.RED))
        sys.exit(1)
    state = load_state(track_name)
    state["current_index"] = idx
    save_state(track_name, state)
    print(clr(f"[{track_label(track_name)}] Exercise set to {n}: {exercises[idx].name}", C.GREEN))

def cmd_tracks():
    print_banner("c23")
    _print_tracks()


# ─── Argument parsing ──────────────────────────────────────────────────────────

def parse_args(argv: list):
    """Return (command, track_name, extra_args)."""
    args = list(argv)

    # extract --track NAME or --track=NAME anywhere in args
    track_name = "c23"
    i = 0
    clean = []
    while i < len(args):
        a = args[i]
        if a.startswith("--track="):
            track_name = a[len("--track="):]
        elif a == "--track" and i + 1 < len(args):
            track_name = args[i + 1]
            i += 1
        else:
            clean.append(a)
        i += 1
    args = clean

    command    = args[0] if args else "watch"
    extra_args = args[1:]
    return command, track_name, extra_args


# ─── Entry point ───────────────────────────────────────────────────────────────

def usage():
    print(__doc__)

def main():
    command, track_name, extra = parse_args(sys.argv[1:])

    if command in ("watch", "w"):
        cmd_watch(track_name)
    elif command in ("list", "ls", "l"):
        cmd_list(track_name)
    elif command in ("hint", "h"):
        cmd_hint(track_name)
    elif command in ("run", "r"):
        cmd_run(track_name)
    elif command == "reset":
        cmd_reset(track_name)
    elif command == "goto":
        if not extra:
            print(clr("goto requires a number, e.g.:  python cfarer.py goto 5", C.RED))
            sys.exit(1)
        try:
            cmd_goto(int(extra[0]), track_name)
        except ValueError:
            print(clr("goto requires a number", C.RED))
            sys.exit(1)
    elif command == "tracks":
        cmd_tracks()
    elif command in ("help", "--help", "-h"):
        usage()
    else:
        print(clr(f"Unknown command: {command!r}", C.RED))
        usage()
        sys.exit(1)

if __name__ == "__main__":
    main()
