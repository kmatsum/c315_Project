c-Monsters Project ===========================================
- All files in this root folder is part of the Command Line Interface (CLI) version

- The "GUIProject" folder is the folder we used for the experimentation of the GUI.
  Everything in the folder should not be moved to the root folder, as they are different projects.



PROGRAM EXECUTION STEPS ======================================
- Install LibCurl4

	sudo apt-get install libcurl4-openssl-dev

  This is used for the Random Number Generator API we used
- Compile program with:

	gcc -o c-monsters c-monsters.c -lcurl

  The last flag is necessary to compile using the API

- RUN c-monsters to run the program