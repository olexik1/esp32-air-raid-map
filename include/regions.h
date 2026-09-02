#pragma once

// Shows the order in which the LEDs are soldered, by region
// 0 - The LED of this region is the first one soldered to the microcontroller
// Helps make it easier to access each LED by the name of the region where it is located 
enum RegionIndex
{
    VOLYN = 0,
    RIVNE,
    ZHYTOMYR,
    CAPITAL,
    CHERNIHIV,
    SUMY,
    POLTAVA,
    KHARKIV,
    LUHANSK,
    DONETSK,
    DNIPRO,
    CHERKASY,
    KYIV,
    KHMELNYTSKYI,
    TERNOPIL,
    LVIV,
    ZAKARPATTIA,
    IVANO_FRANKIVSK,
    CHERNIVTSI,
    VINNYTSIA,
    KROPYVNYTSKYI,
    ODESA,
    MYKOLAIV,
    KHERSON,
    ZAPORIZHZHIA,
    CRIMEA,
    NUM_REGIONS,
    SEVASTOPOL
};

// Shows the order in which information about alerts in string is sent 
constexpr RegionIndex apiToLedMap[] = {
    CRIMEA,
    VOLYN,
    VINNYTSIA,
    DNIPRO,
    DONETSK,
    ZHYTOMYR,
    ZAKARPATTIA,
    ZAPORIZHZHIA,
    IVANO_FRANKIVSK,
    CAPITAL,
    KYIV,
    KROPYVNYTSKYI,
    LUHANSK,
    LVIV,
    MYKOLAIV,
    ODESA,
    POLTAVA,
    RIVNE,
    SEVASTOPOL,
    SUMY,
    TERNOPIL,
    KHARKIV,
    KHERSON,
    KHMELNYTSKYI,
    CHERKASY,
    CHERNIVTSI,
    CHERNIHIV
};