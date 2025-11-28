#!/bin/bash

echo 'echo "42 is nice" | -q ./ft_ssl md5'
echo "42 is nice" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5
echo '------'
echo "42 is nice" | openssl md5
echo '================================='

echo 'echo "42 is nice" | ./ft_ssl md5'
echo "42 is nice" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5
echo '------'
echo '(stdin)= 35f1d6de0302e2086a4e472266efb3a9'
echo '================================='

echo 'echo "42 is nice" | ./ft_ssl md5 -p'
echo "42 is nice" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -p
echo '------'
echo '("42 is nice")= 35f1d6de0302e2086a4e472266efb3a9'
echo '================================='

echo 'echo "Pity the living." | ./ft_ssl md5 -q -r'
echo "Pity the living." | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -q -r
echo '------'
echo 'e20c3b973f63482a778f3fd1869b7f25'
echo '================================='

echo 'echo "And above all," > file'
echo "And above all," > file
echo './ft_ssl md5 file'
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 file
echo '------'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo '================================='
echo './ft_ssl md5 -r file'
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -r file
echo '------'
echo '53d53ea94217b259c11a5a2d104ec58a file'
echo '================================='

echo './ft_ssl md5 -s "pity those that arent following baerista on spotify."'
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -s "pity those that arent following baerista on spotify."
echo '------'
echo -n 'MD5 ("pity those that arent following baerista on spotify.") = '
echo -n "pity those that arent following baerista on spotify." | md5sum
echo 
echo '================================='

echo 'echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file'
echo "be sure to handle edge cases carefully" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -p file
echo '------'
echo '("be sure to handle edge cases carefully")= 3553dc7dc5963b583c056d1b9fa3349c'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo '================================='

echo 'echo "some of this will not make sense at first" | ./ft_ssl md5 file'
echo "some of this will not make sense at first" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 file
echo '------'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo '================================='

echo 'echo "but eventually you will understand" | ./ft_ssl md5 -p -r file'
echo "but eventually you will understand" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -p -r file
echo '------'
echo '("but eventually you will understand")= dcdd84e0f635694d2a943fa8d3905281'
echo '53d53ea94217b259c11a5a2d104ec58a file'
echo '================================='

echo 'echo "GL HF lets go" | ./ft_ssl md5 -p -s "foo" file'
echo "GL HF lets go" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -p -s "foo" file
echo '------'
echo '("GL HF lets go")= d1e3cc342b6da09480b27ec57ff243e2'
echo 'MD5 ("foo") = acbd18db4cc2f85cedef654fccc4a4d8'
echo 'MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a'
echo '================================='

echo 'echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"'
echo "one more thing" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -r -p -s "foo" file -s "bar"
echo '------'
echo '("one more thing")= a0bd1876c6f011dd50fae52827f445f5'
echo 'acbd18db4cc2f85cedef654fccc4a4d8 "foo"'
echo '53d53ea94217b259c11a5a2d104ec58a file'
echo 'ft_ssl: md5: -s: No such file or directory'
echo 'ft_ssl: md5: bar: No such file or directory'
echo '================================='

echo 'echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file'
echo "just to be extra clear" | valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes -q ./ft_ssl md5 -r -q -p -s "foo" file
echo '------'
echo '3ba35f1ea0d170cb3b9a752e3360286c'
echo 'acbd18db4cc2f85cedef654fccc4a4d8'
echo '53d53ea94217b259c11a5a2d104ec58a'