python lisp-fsa-gen.py fsa.txt   // generates the Lisp program part2.lsp
timeout /t 2                     // wait for first program to finish
xlwin32 part2.lsp                // invoke xlwin32.exe with generated fsa processor