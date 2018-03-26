# AutomateGitignoreGen
Generates gitignore based on difference between extensions before and after compilation

## Introduction
The purpose of this program is to learn and practice with some new features and elements of C++17, as std::filesystem. 
Taking over a project that has been managed in a different versioning system than Git will not have .gitignore file
and then, some has to be created. This is mainly to avoid to include files that are generated during compilation and,
because so, are not to be included in the repository.

## Usage
To create a text file containning the extensions of the repository (before compilation) run the program with the path 
of the repository as a parameter. Then the file will be created in the folder the program is located. The file will 
contain the different extensions found in the files with the dot before the extension.

When you want to check if new file extensions were created in compilation (as, for example, object files) you pass as
parameters the name of the created file with the extensions and as second parameter the path to the repository. Once
it finished, if there is any new extension for any files in the repository generated in the compilation, the program
will create the .gitignore file in the root folder of the repo (the path you fed the program with).

## Comments
This software will be useful in a few situations. Usually, projects are configured to get rid of the objetc files once
the compilation is a success. But sometimes, there is no cleaning after compilation and there are several intermediate files
that are not needed. However, in some cases, those have common extensions so they will not be excluded.

So, as said, this is an "academic" work to practice the use of the new std::filesystem of C++14. Feel free to add or impove
it and let me know. Regards.
VHM
