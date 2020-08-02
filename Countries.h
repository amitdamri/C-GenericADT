

#ifndef COUNTRIES_H_
#define COUNTRIES_H_
#include "Defs.h"
/*************************************************************************************
 ********************************STRUCTS DEFENITIONS**********************************
 *************************************************************************************/
typedef struct Country* Country;

typedef struct City* City;

typedef struct GeographicArea* GeographicArea;


/**************************************************************************************
 ********************************FUNCTIONS DECLARATIONS********************************
 **************************************************************************************/

/*adds country by setting its name and geographic area and return pointer to new object*/
Country addCountry(char*, int, int, int, int);

/*add city to given country and return true, if the operation didn't succeed return false*/
status addCity (Country, char*, char*, int);

/*remove given city from given country and return true, if the city wasn't found return false*/
status removeCity(Country, char*);

/*check if given coordinate is in given country geographic area and return true or false accordingly*/
bool isCoordinateInCountry (Country, int, int);

/*free memory of given country*/
status freeAllocatedMemoryOfCountry(Element);

/*deep copy of country object*/
Element deepCopyOfCountryObject(Element);

/*print country details*/
status printCountry (Element);

/*check whether city is in given country*/
bool searchCity(Country, char*);

//checks if two countries are equal according to their name
bool isEqualCountry(Element, Element);

//converts a country name to a number according to its ascii number
int transformCountryIntoNumberFunction(Element);

//prints the name of the country
status prinCountryName(Element);

//frees the country name memory
status freeCountryName(Element);

//copies the country name
Element copyCountryName(Element);


#endif /* COUNTRIES_H_ */
