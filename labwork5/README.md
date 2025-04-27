# Лабораторная работа 5

## API
### ArgParser class
```cpp
    // String arguments
    ArgParser& AddStringArgument( std::string long_name );
    ArgParser& AddStringArgument( short_name, std::string long_name );
    ArgParser& AddStringArgument( std::string long_name, std::string description );
    ArgParser& Default( std::string );
    ArgParser& StoreValue( std::string );
    ArgParser& MultiValue( size_t = 0 );
    ArgParser& Positional();
    
    // Int arguments
    ArgParser& AddIntArgument( std::string long_name );
    ArgParser& AddIntArgument( char short_name, std::string long_name );
    ArgParser& AddIntArgument( std::string long_name, std::string description );
    ArgParser& StoreValues( std::vector<int> values );
    
    // Flag arguments
    ArgParser& AddFlag(const std::string& long_name);
    ArgParser& AddFlag(char short_name, const std::string& long_name);
    ArgParser& AddFlag(const std::string& long_name, const std::string& description);
    ArgParser& StoreValue(bool& value);
    
    // Help
    ArgParser& AddHelp(char short_name, const std::string& long_name, const std::string& description);
    
    // Parsing
    bool Parse(int argc, char** argv);
    bool Parse(const std::vector<std::string>& args);
    
    // Getters
    std::string GetStringValue(const std::string& name, size_t index = 0) const;
    int GetIntValue(const std::string& name, size_t index = 0) const;
    bool GetFlag(const std::string& name) const;
    
    // Help
    bool Help() const;
    std::string HelpDescription() const;
```
