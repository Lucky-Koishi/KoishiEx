# KoishiEx
恋恋のEX API以及黑猫版以及白猫版源代码

KoishiEx文件夹是自己做的EXAPI；
ExRabbit文件夹是黑猫版的源代码，目前更新至黑猫.4.9。
ExParrot文件夹是白猫版的源代码，目前更新至白猫.2.2。

EXAPI是完全开源的，可以随意使用（不过似乎要设置一下ZLIB和LIBPNG相关的一些林林总总东东，比如说debug版本需要忽略特定默认库libcmt.lib等），如果大家发现有什么BUG或者有什么帮助改进API的想法可以联系我 swablu@qq.com 
对于VS2015以上版本，你需要重新对ZLIB和LIBPNG进行编译，并用编译后的LIB文件替换到源代码里的这些文件后才能使用。

EXAPI支持NPK、IMG等文件的大部分操作，支持的IMG类型包括V2、V4、V5、V6。

更新履历(Black).txt记录了黑猫版各版本的更新履历。更新履历(White).txt记录了白猫版各版本的更新履历。


Source Code of Koishi's EX API and BlackCat version and WhiteCat version.

The folder "KoishiEx" is the source code of API made by myself.
The folder "ExRabbit" is the source code of the BlackCat version, which has currently updated to BlackCat.4.9.
The folder "ExParrot" is the source code of the WhiteCat version, which has currently updated to WhiteCat.2.2.

The API is completely opened and can be used freely(But you seem to setup your project for ZLIB and LIBPNG, such as the ignoring default library "libcmt.lib" when using the DEBUG mode, etc.). Please contact me if you find any bugs or have an idea for helping improve the API. Email: swablu@qq.com
If your Visual Studio's version is VS2015 or higher, you need to recompile ZLIB and LIBPNG and replace the files in source code by the generated files.

The API supports the most operations for dealing the format of NPK and IMG, with the IMG version of 2, 4, 5 and 6.

The file "更新履历(Black).txt" records the update history of Koishi's Ex BlackCat version. The file "更新履历(White).txt" records the update history of Koishi's Ex WhiteCat version.

 