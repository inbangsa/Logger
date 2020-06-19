# Logger Lib

### [1] Introduction 

Logging is an important part in the software development and helps for troubleshooting when something goes wrong in the software at customer side. To reproduce the scenario properly,  logging of messages at appropriate severity level is a must.This  is an attempt to make pythonic way of logging like obj.debug("sample message");  and Macro based Logging logger::DEBUG("sample message"). 

### [2] Usage

### [2A] Different Ways to Log messages

There are two ways to log  the messages using this lib as described below :-  

### 1. Object Based Approach 
 
 * Create an Object of class Logger .
 * Log the message at an appropriate levels.

Example 

``` csharp
logger::Logger log_obj; 
log_obj.Debug("sample message");  
```

### 2. Macro Based Approach

Example

```csharp
logger::DEBUG("sample message"); 
```
### [2B] Logging Messages at various log levels.

Messages can be logged at OFF,FATAL,ERROR,DEBUG,WARN,TRACE levels.

### 1. Object Based Approach 
 
Example 

``` csharp
logger::Logger log_obj; 
log_obj.Log(logger::log_level::ERROR,"sample message");//using Log function.
log_obj.Fatal("some message"); //directly logging at a particular level.  
```

### 2. Macro Based Approach

Example

```csharp
logger::LOG(logger::log_level::ERROR,"sample message");//using LOG function.
logger::FATAL("some message");//directly logging at a particular level. 
```

## [3] Configuration
### [3A] Log Levels and their Severity Order

There are 5 log levels at which message will be logged namely:-
* OFF -> HIGHEST SEVERITY 
* FATAL 
* ERROR
* DEBUG 
* WARN 
* TRACE--> LOW SEVERITY 

### [3B] Selective Logging

This feature enables user to filter or log those message only which are equal or  higher in severity level than the  desired log level.

Example 

```csharp
logger::Logger log_obj;    
log_obj.SetLogLevel(logger::log_level::DEBUG);
```

Here all the messages which are at higher priority i.e. OFF, FATAL, ERROR and DEBUG will be logged and rest will be ignored.
 
### [3C] Changing Logger Name

By default logger names is  "default logger" and can be changes via following methods :- 

a) Using Object

```csharp
logger::Logger log_obj;
log_obj.SetLoggerName("new logger name");
```
b)Using MACRO 

```csharp
logger::SET_LOGGER_NAME("new logger name");
```
### [3D] Default Formatter and Default Sink

**1. Default Formatter**

Default formatter formats the data and places in square brackets form as described below:-

[A] For object based method : Only essential parameters will be logged.

```txt
[logger name][log level][message]
```

[B] For Macro based Approach : Captures extra information other than essential ones.

```txt
[date][time][filename][line number][calling function name][logger name][logger level][message] `
```

**2. Default Sink**

This accepts the default formatter as an parameter and records the data  in **logs.txt file** for both the methods.

**Note**
1. One method will not affect the setting to other one.  
2. By default all the log messages will be logged in the same logs.txt file irrespective of any method .
3. To change the filename for a particular  method  say Object based Approach use :-
 
```cpp
auto sink=std::make_shared<logger::DefaultSink>();
sink->SetFileName("desired_file_name.txt");
log_obj->SetSink(sink);
```
and similarly for macro based approach.

### [3E] Creating user defined Formatter and Sink.

User defined Formatter can be created by deriving the class from abstract class IFormatter .

Example 

```cpp
class UserDefinedFormatter::public IFormatter
{
private:
 std::string format(const std::string& msg,const logger::log_level& log_level,const std::string& logger_name,const logger::internal::ExtractedLogCredentials& log_credentials) override
 {
    //User defined definition to format the data.   
 }
};

// User defined sink can be File, database, anyserver etc which can implemented easily by deriving class from the abstract class ISink as shown below:-

class UserdefinedSink: public ISink
{
void record(const std::string& msg,
    const logger::log_level& log_level,
    const std::string& logger_name,
    const logger::internal::ExtractedLogCredentials& log_credentials) override
  {
    auto formatted_data = formatter_ptr->FormatData(msg, log_level, logger_name, log_credentials);
    //user defined definition to record the data to a sink.    
  }
};
```


### [4] Installation

**1. Header only library**

Just include the include directory.
```cmake
add_executable(<user_target_name> <user source file>)
target_include_directories(<user_target_name> INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)
```

**2. Direct Linking**

Logger is implemented as interface library and can be linked as follows:-

```cmake
add_executable(<user_target_name> <user source file>)
target_link_libraries(<user_target_name> logger_lib)
```

**3. Using find_package()**

```cmake 
find_package(logger_lib)
if(logger_lib_FOUND) 
{
 add_executable(<user_target_name> <user_source_file>)
 target_link_libraries(<user_target_name> logger_lib)
}
endif()
```

### [5] TODO
* Implementing various types of sink like daily logger etc. 
