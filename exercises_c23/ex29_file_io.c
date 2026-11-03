// CFarer Exercise 29: File I/O
// TOPIC: fopen, fprintf, fclose, fscanf
// DIFFICULTY: Advanced
//
// C file I/O uses FILE* handles.
//   fopen(path, mode)  -> FILE* (NULL on failure)
//   fprintf(fp, ...)   -> write formatted text
//   fclose(fp)         -> flush and close
//
// Task:
//   1. Open "numbers.txt" for writing ("w").
//   2. Write the integers 1..5, one per line.
//   3. Close the file.
//   4. Re-open it for reading ("r") and read back the 5 values.
//   5. Assert they equal 1..5, then close and remove the file.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
    const char *path = "numbers.txt";

    // --- write ---
    FILE *fw = fopen(path, "w");
    assert(fw != NULL);

    // TODO: write integers 1..5 with fprintf

    fclose(fw);

    // --- read back ---
    FILE *fr = fopen(path, "r");
    assert(fr != NULL);

    for (int i = 1; i <= 5; i++) {
        int val = 0;
        // TODO: read one integer with fscanf(fr, "%d", &val)
        assert(val == i);
    }

    fclose(fr);
    remove(path);   // clean up temp file

    printf("File I/O works correctly!\n");
    return 0;
}

// I AM NOT DONE
