# KoishiEx
������EX API�Լ����Ӱ�Դ����

KoishiEx�ļ������Լ�����EXAPI��
ExRabbit�ļ��������Ӱ��Դ���룬Ŀǰ����������.5.1��

EXAPI����ȫ��Դ�ģ���������ʹ�ã������ƺ�Ҫ����һ��ZLIB��LIBPNG��ص�һЩ�������ܶ���������˵debug�汾��Ҫ�����ض�Ĭ�Ͽ�libcmt.lib�ȣ��������ҷ�����ʲôBUG������ʲô�����Ľ�API���뷨������ϵ�� swablu@qq.com 
����VS2015���ϰ汾������Ҫ���¶�ZLIB��LIBPNG���б��룬���ñ�����LIB�ļ��滻��Դ���������Щ�ļ������ʹ�á�

EXAPI֧��NPK��IMG���ļ��Ĵ󲿷ֲ�����֧�ֵ�IMG���Ͱ���V2��V4��V5��V6��

mplserial.txt��¼�˸�ͼ���ƴ��˳��
BUGTRACE.txt��¼�����Ӱ���汾�ĸ���������


Koishi's EX API and the source code of the Rabbit version.

The folder "KoishiEx" is the source code of API made by myself.
The folder "ExRabbit" is the source code of the Rabbit version, which has currently updated to Rab.5.1.

The API is completely opened and can be used freely(But you seem to setup your project for ZLIB and LIBPNG, such as the ignoring default library "libcmt.lib" when using the DEBUG mode, etc.). Please contact me if you find any bugs or have an idea for helping improve the API. Email: swablu@qq.com
If your Visual Studio's version is VS2015 or higher, you need to recompile ZLIB and LIBPNG and replace the files in source code by the generated files.

The API supports the most operations for dealing the format of NPK and IMG, with the IMG version of 2, 4, 5 and 6.

The file "mplserial.txt" records the splice order of the avatars of the characters in DNF.
The file "BUGTRACE.txt" records the update history of Koishi's Ex Rabbit version.