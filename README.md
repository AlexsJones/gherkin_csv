gherkin_csv
==========


Converts a feature file into a csv e.g. demo.feature => demo.csv

![Vim](doc/vim.png)
------------------------
![Excel](doc/excel.png) 

Example output: https://github.com/AlexsJones/gherkin_csv/blob/master/test/demo.csv

##usage

```
$>gherkin_csv --feature demo.feature
```
###Deps
```
cmake
```
- OS/X install with `brew install cmake`
- Linux install with a package manager (e.g. yum install cmake || apt-get install cmake)
- Manual install http://www.cmake.org/cmake/resources/software.html

##Download (Pre-built)

####Mach OSX 64bit
[!Here](https://github.com/AlexsJones/gherkin_csv/raw/master/bin/gherkin_csv)


##Installation (Built it yourself)

```
git clone https://github.com/AlexsJones/gherkin_csv.git
```

Build deps first
```
git submodule init
git submodule update
cd jnxlibc
cmake .
make
sudo make install 
cd ../
```
Now build the parser
```
cmake
make 
sudo make install
```

##Todo
- Correctly free all memory and data structures after use for sake of cleanliness
- Custom fields e.g. iPad4, iPhone5s
- More configuration options
- Multiple input files
