#include "currencymodel_plugin.h"
#include "currencymodel2.h"

#include <qqml.h>

void CurrencyModelPlugin::registerTypes(const char *uri)
{
    // @uri harbour.currencyconverter.currencies
    qmlRegisterType<CurrencyModel2>(uri, 1, 0, "CurrencyModel");
}


