gherkin_csv
==========


Converts a feature file into a csv e.g. demo.feature => demo.csv

![Vim](doc/vim.png)
![Excel](doc/excel.png) 

Example output: https://github.com/AlexsJones/gherkin_csv/blob/master/test/demo.csv

##usage

```
$>gherkin_csv --feature demo.feature
```

##Installation

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

###Deps

```
cmake
```

##Todo

- Custom fields e.g. iPad4, iPhone5s
- More configuration options
- Multiple input files
