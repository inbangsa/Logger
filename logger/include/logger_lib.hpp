#ifndef LOGGER_LIB_HPP
#define LOGGER_LIB_HPP

#include <string>
#include <memory>

//Macros to extract the information.
#define FLAG_ON(...)  logger::ExtractAllCredentials::extract_all_credentails(__DATE__,__TIME__,__FILE__,__LINE__,__FUNCTION__)
#define FLAG_OFF(...) logger::ExtractMinimumCredentials::extract_minimum_credentials(__DATE__,__TIME__)

namespace logger
{
	//Data structure for storing  extracted log credentials example file_name etc.
	struct LogCredentails
	{
		std::string date = "";
		std::string time = "";
		std::string file_name = "";
		std::string function_name = "";
		int line_number=0;
	};

	//Extracting minimum log credentails eg. date and time.
	struct ExtractMinimumCredentials
	{
		static std::shared_ptr<logger::LogCredentails> extract_minimum_credentials(std::string date_, std::string time_);
		
	};

	//Extracting all log credentails eg. date , time, line number, function name etc.
	struct ExtractAllCredentials
	{
		static std::shared_ptr<logger::LogCredentails> extract_all_credentails(std::string date_, std::string time_, std::string file_name_, int line_number_, std::string function_name_)
	};


	static std::shared_ptr<logger::LogCredentails> logger::ExtractMinimumCredentials::extract_minimum_credentials(std::string date_,std::string time_)
	{
		std::shared_ptr<logger::LogCredentails> extracted_minimum_data;
	
		extracted_minimum_data->date = date_;
		extracted_minimum_data->time = time_;
		
		return extracted_minimum_data;
	}

	static std::shared_ptr<logger::LogCredentails> logger::ExtractAllCredentials::extract_all_credentails(std::string date_, std::string time_,std::string file_name_,int line_number_,std::string function_name_ )
	{
		std::shared_ptr<logger::LogCredentails> extracted_all_data;

		extracted_all_data->date = date_;
		extracted_all_data->time = time_;
		extracted_all_data->file_name = file_name_;
		extracted_all_data->function_name = function_name_;
		extracted_all_data->line_number = line_number_;
		
		return extracted_all_data;
	}
}
#endif()