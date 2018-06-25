ASCII Obfuscation
=================

This is a small example program to show / have fun with `ASCII` characters and the way we can easily obfuscate them

Some details :
--------------

### Small talk about where such a dumb idea comes from : ###

I started this project being very angry at a collegue at work. We had a strong argument about C language programming
practices. Precisely about wether we should use _inline if_ operations in macro or not. Moreover with or without 
explicative comments  He said something like : "_There is no point arguing about this, the code is quite clear about
what's happening_". <br>
My point was, and is still : macros are quite hard to debug and using _inline if_ operations only obfuscates the code.
Code should be documented and commented to express the will of the programmer if he wants the code to be well understood.
Since you're in a team, there will be people reading your code and, maybe someday, you will be gone, and somebody else
will end up maintaining your code. In case the code is "_self-documented_" or "_cristal clear_" (I've heard this countless
times), there is a non null probability that the code is not as clear as expected (see this 
[amazing strip](https://www.commitstrip.com/en/2014/09/15/when-i-stumble-upon-self-documented-code/) about it) nor 
enough self-documenting. The final result being throwing away the code and starting the whole thing again. But,
inventing the wheel twice is quite useless and "[_good code does not rust_](https://www.joelonsoftware.com/2000/04/06/things-you-should-never-do-part-i/)"
as long as the system for which it is written is not deprecated.

So, I decided to write a small programm that abused _inline if_ operations to be as obscure as possible and which
will only print out to the console the message : "_You know my point about inline_ if operations _, they only obfucate
the code_". I knew that, if I succeeded, I could submit it to the [IOCCC](http://ioccc.org/), but that was not the
initial goal.

So I decided to go with a program which would obfuscate a string passed as parameter. But, while writting the very first
lines of code to the project, I was in need of some comments and notes to keep myself informed about the point at which
my work would stop before I would resume it later on. Then I ended up turning the whole project into the opposite concept
I wanted to lampoon : documented, commented and organised code. I might try to create an obfuscated version of it once
it's fincished, but I am definetely not sure about it anymore.

### Coding rules used in this project ###

You might want to have a look at [this page](./documentation/blog/coding_style.md)

Repository content :
--------------------

- **.git** : _GIT_ version control files. **DO NOT EDIT** unless you know precisely what you're doing.
- **sources** : Project source files directory. The final binary file will be compiled from these source code files.
- **project** : This directory contains IDE related project files. Only [Code::Blocks](http://www.codeblocks.org/) is used at the moment
- **documentation** : Documentation directory.
  - **blog** : _Markdow_ files used for Jekyll blog posts
  - **html** : [_HTML Doxygen_](http://www.stack.nl/~dimitri/doxygen/manual/starting.html#html_out) generated documentation directory. This directory is empty on purpose.
  - **latex** : [_LaTeX Doxygen_](http://www.stack.nl/~dimitri/doxygen/manual/starting.html#latex_out) generated documentation directory. This directory is empty on purpose
  - _ascii_obfuscation.doxygen.cnfg_ : [_Doxygen_](http://www.stack.nl/~dimitri/doxygen/index.html) configuration file
  - _generdoc.bat_ : _MicroSoft Windows_ ```.bat``` script used to automatically generate the _Doxygen_ documentation. Double-click on this to generate the documentation.<br>
    _IMPORTANT :_ You should have the *Ubuntu* subsytem with _Doxygen_ installed on your computer in order to use this script.
- _.gitignore_ : _GIT_ ignore file. This allows us to exclude automatically generated files and directory from the project
- __config.yml_ : _Jekyll_ configuration file
- _LICENSE_ : Project licence file. [_GNU GPL3_](https://www.gnu.org/licenses/gpl-3.0.html) is used here.
- _README.md_ : This file.


Miscealeanous :
---------------

Some basic informations and templates about _README_ file and _Jekyll_ can be found [here](./documentation/blog/readme_template.md)