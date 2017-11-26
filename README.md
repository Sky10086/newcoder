# newcoder
for reviewing basic algorithms.

## Here now have these algorithms and unit tests respectively

### sort algorithm
- bubble sort
- select sort
- insetr sort
- merge sort
- quick sort
- heap sort
- radix sort
### string process
- KMP algorithm
- Manacher algorithm

### other coming soon

Usage
====
### 1 requirement
- install [cmake](https://github.com/Kitware/CMake)
### 2 install
- for mac`s xcode
```
git clone git@github.com:Sky10086/newcoder.git
cd newcoder
cd buildXcode
./genXcode.sh #or bash genXcode.sh
```

## there are some error in the visual studio 2013 when run this project,but in xcode is fine,sorry to windows`s user.I will fix thix as soon as posiable : (.
- for windows`s vs studio 12,the other version just modify the "Visual Studio 12"
```
git clone git@github.com:Sky10086/newcoder.git
cd newcoder
mkdir buildSln
cd buildSln
cmake .. -DDEBUG=true -G "Visual Studio 12" 
```
