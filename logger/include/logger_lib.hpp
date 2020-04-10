#ifndef LOGGER_LIB_HPP
#define LOGGER_LIB_HPP

#include <string>
#include <memory>

namespace logger
{
	/**
	* @brief  Log level with their severity order , 0 =>high priority , 5=> least priority. 
	*/
	enum class LEVEL = { OFF = 0, FATAL = 1, ERROR = 2,WARN = 3,DEBUG = 4,TRACE = 5 };

	/**
	* @brief  Interface for the extracted log data like file name , function name etc , one may extend for more parameters such as number of argumnets __VA_ARGS__.
	*/
	struct IExtarctedLogCredentials
	{
		std::string file_name = "";
		std::string function_name = "";
		int line_number = 0;
	};

	/**
	* @brief  Interface for formatting the given data.
	*/
	class IFormatter
	{
	public:
		/**
		* @brief Sets format pattern.
		* @param pattern formatting pattern 
		* @retval std::string
		*/
		void set_format_pattern(std::string pattern);

		/**
		* @brief Returns formatting pattern.
		* @param None
		* @retval std::string
		*/
		std::string get_format_pattern() const;

		/**
		* @brief Formats the given data.
		* @param msg log message
		* @param level log level
		* @param logger_name default name is root
		* @param log_credentials extracted log credentials 
		* @retval std::string
		*/
		template<typename T>
		virtual std::string  format(T msg, logger::LEVEL level, std::string& logger_name, std::shared_ptr<logger::IExtarctedLogCredentials>& log_credentials) = 0;

	private:
		std::string format_pattern;
	};


	/**
	* @brief  Interface for defining where the log has to be written/dumped to eg. file, datebase, webserver etc.  
	*/
	class ISink
	{
	public:

		/**
		* @brief  Sets the sink option.
		* @params sink data writing option
		* @retval None
		*/
		void set_sink(std::string sink);

		/**
		* @brief  Returns the sink option.
		* @params None
		* @retval std::string
		*/
		std::string get_sink() const;

		/**
		* @brief  User defined sink option.
		* @params sink data writing option
		* @retval std::string
		*/
		virtual std::string sink(std::string sink) = 0;

	private:
		std::string sink;
	};


	/**
	* @brief  Interface for checking severity level.
	*/
	class ICheckSeverityLevel
	{
	public:
		/**
		* @brief Checks the severity level against  the preferred severity level.
		* @params preferred_severity_level 
		* @params test_severity_level 
		* @retval bool
		*/
		virtual bool check_severity_level(logger::LEVEL preferred_severity_level, logger::LEVEL test_severity_level) = 0;
	};

	/**
	* @brief  Interface for recording the formatted data to the sink following the severity criterion.
	*/
	template<typename T>
	class IRecorder
	{
	public:
		/**
		* @brief  Ctor.
		* @params i_check Used for  checking severity criterion.
		* @params i_formatter Used for  formatting  data.
		* @params i_sink Used for writing/dumping options may be to a file etc.
		* @retval std::string
		*/
		IRecorder(std::shared_ptr<logger::ICheckSeverityLevel>& i_check, std::shared_ptr<logger::IFormatter>& i_formatter, std::shared_ptr<logger::ISink>& i_sink);
	
		/**
		* @brief  Records the data to a particular sink .
		* @params msg log message
		* @params level log level
		* @params logger_name  logger name
		* @params extracted_data log credentials
		* @retval bool
		*/
		virtual bool record(T& msg, logger::LEVEL& level, std::string& logger_name, std::shared_ptr<logger::IExtarctedLogCredentials>& extracted_data) = 0;
	
	private:
		std::shared_ptr<logger::IFormatter> i_formatter;
		std::shared_ptr<logger::ISink> i_sink;
		std::shared_ptr<logger::ICheckSeverityLevel> i_check;
	};

	//Implemtation of methods of class IFormatter.
	void IFormatter::set_format_pattern(std::string pattern)
	{
		this->format_pattern = pattern;
	}

	std::string IFormatter::get_format_pattern() const
	{
		return format_pattern;
	}

	//Implementation methods of class ISink .
	void ISink::set_sink(std::string sink)
	{
		this->sink = sink;
	}
	std::string ISink::get_sink() const
	{
		return sink;
	}

	//Implementation  of methods of class IRecorder.
	template<typename T>
	IRecorder<T>::IRecorder<T>(std::shared_ptr<logger::ICheckSeverityLevel>& i_check, std::shared_ptr<logger::IFormatter>& i_formatter, std::shared_ptr<logger::ISink>& i_sink) :
		i_check(i_check), i_formatter(i_formatter), i_sink(i_sink)
	{
	}
};
#endif()