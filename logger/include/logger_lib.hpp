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

	//Implemtation of methods of class IFormatter.
	void IFormatter::set_format_pattern(std::string pattern)
	{
		this->format_pattern = pattern;
	}

	std::string IFormatter::get_format_pattern() const
	{
		return format_pattern;
	}

};
#endif()