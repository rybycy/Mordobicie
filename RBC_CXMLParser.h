#ifndef RBC_CXMLPARSER_H
#define RBC_CXMLPARSER_H

#include "tinyxml/tinyxml.h"

class RBC_CXMLParser
{
	private:
			static TiXmlDocument* doc; /**< Buffer document */
	public:
			static const char* RBC_GetXMLData(const char* childa, const char* arg, int number);

			static const char* RBC_GetXMLData(const char *childa, int number=0);

			static const char* RBC_GetXMLValue(const char* childa, const char* childb, int number);

			static const char* RBC_GetXMLValue(const char* childa, const char* childb, const char* childc, int number);

			static const char* RBC_GetXMLKey(const char* childa, const char* childb, int number);

			static const char* RBC_GetXMLData(const char* childa, const char* childb, const char* arg, int number);

			static const char* RBC_GetXMLData(const char* childa, const char* childb, const char* childc, const char* arg, int number);

			static const char* RBC_GetXMLText(const char* childa, const char* childb, int no, int number);

			static const char* RBC_GetXMLText(const char* childa, const char* childb, int number);

			static const char* RBC_GetXMLText(const char* childa, const char* childb, const char *childc, int number);

			static bool RBC_LoadXMLFile(const char *path);
};

#endif // RBC_CXMLPARSER_H
