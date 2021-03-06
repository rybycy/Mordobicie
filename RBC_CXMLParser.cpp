#include "RBC_CXMLParser.h"

TiXmlDocument* RBC_CXMLParser::doc;

bool RBC_CXMLParser::RBC_LoadXMLFile(const char* path){
	delete doc;
	doc=new TiXmlDocument(path);
	if(!doc->LoadFile()){return 0;}
	return 1;
}

const char* RBC_CXMLParser::RBC_GetXMLData(const char* childa, const char* childb, const char* childc, const char* arg, int number=0){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).FirstChild(childc).ChildElement(number).Element();
	if(child){return child->Attribute(arg);}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLValue(const char* childa, const char* childb, int number=0){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).ChildElement(number).Element();
	if(child){return child->Value();}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLValue(const char* childa, const char* childb, const char* childc, int number=0){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).FirstChild(childc).ChildElement(number).Element();
	if(child){return child->Value();}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLData(const char* childa, const char* childb, const char* arg, int number=0){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).ChildElement(number).Element();
	if(child){return child->Attribute(arg);}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLData(const char* childa, const char* arg, int number=0){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).ChildElement(number).Element();
	if(child){return child->Attribute(arg);}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLText(const char* childa, const char* childb, int no, int number){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).ChildElement(no).ChildElement(number).Element();
	if(child){return child->GetText();}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLText(const char* childa, const char* childb, int number){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).FirstChild().ChildElement(number).Element();
	if(child){return child->GetText();}else{return NULL;}
}

const char* RBC_CXMLParser::RBC_GetXMLText(const char* childa, const char* childb, const char* childc, int number){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).FirstChild(childc).ChildElement(number).Element();
	if(child){return child->GetText();}else{return NULL;}
}


const char* RBC_CXMLParser::RBC_GetXMLKey(const char* childa, const char* childb, int number){
	TiXmlHandle docHandle(doc);
	TiXmlElement* child = docHandle.FirstChild(childa).FirstChild(childb).FirstChild().ChildElement(number).Element();
	if(child){return child->Value();}else{return NULL;}
}
