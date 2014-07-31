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
cmake
make 
sudo make install
```

###Deps

```
cmake
jnxlibc (https://github.com/AlexsJones/jnxlibc)
```

##Todo

- Custom fields e.g. iPad4, iPhone5s
- More configuration options
- Multiple input files
