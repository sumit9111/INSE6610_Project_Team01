* `src` is for anything source-related of your project touches that, such as Forensic Lucid specifications, code modifications and patches to external tools, any other scripts, etc. Place your code work under `teamX` subdirectory.
* `gipc` is a General Intensional Program Compiler (framework) that has a Forensic Lucid parser. To parse (under Linux, OS X terminal, or Bash shell under Cygwin on Windows):

```
./gipc --flucid your-filename.ipl
```

You can also use it on the command line directly via Java:

```
java -jar gipc.jar --flucid your-filename.ipl
```
