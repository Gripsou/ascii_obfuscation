[Back to Home page](../../README.md)

Small talk about where such a dumb idea comes from
==================================================

I started this project being very angry at a collegue at work. We had a strong argument about _C language_ programming
best practices. Precisely about wether we should use _inline if_ operations in macro or not. Moreover with or without
explicative comments. He said something like : "_There is no point arguing about this, the code is quite clear about
what's happening_".

My point was, and is still : macros are quite hard to debug and using _inline if_ operations only obfuscates the code.
We better ban them, just like ```goto```, since their use is not compulsory for the language to work. I also think that
code should be documented and commented to express the will of the programmer if he wants the code to be well understood.

If you're wondering why I am giving so much importance to this, I might tell you that, if you are a programmer
you are very likely to work in a team. There will be people reading your code and, maybe someday, you will be gone, and
somebody else will end up maintaining your code. In case the code is "_self-documented_" or "_cristal clear_" (I've
heard this countless times), there is a non null probability that the code is not as clear as expected
[nor enough self-documenting](https://www.commitstrip.com/en/2014/09/15/when-i-stumble-upon-self-documented-code/). 
The final result being throwing away the code and starting the whole thing again. But,
inventing the wheel twice is quite useless and, because "[_good code does not rust_](https://www.joelonsoftware.com/2000/04/06/things-you-should-never-do-part-i/)",
it is a complete waste of time to write it all again from scratch as long as the system for which it is written is not
deprecated.

So, I decided to write a small programm that abused _inline if_ operations to be as obscure as possible and which
will only print out to the console the message : "_You know my point about inline_ if operations _, they only obfucate
the code_". I knew that, if I succeeded, I could submit it to the [IOCCC](http://ioccc.org/), but that was not the
initial goal.

So I decided to go with a program which would obfuscate a string passed as parameter. But, while writting the very first
lines of code to the project, I was in need of some comments and notes to keep myself informed about the point at which
my work would stop before I would resume it later on. Then I ended up turning the whole project into the opposite of the
concept I wanted to lampoon : documented, commented and organised code. I wondered about it for some days and, maybe
this change is for good. I may use it as an example of what I consider the best coding practice in _C_. 

I might try to create an obfuscated version of it once it's finished, but I am definetely not sure about it anymore.
