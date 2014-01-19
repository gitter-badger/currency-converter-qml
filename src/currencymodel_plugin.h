#ifndef CURRENCYMODEL_PLUGIN_H
#define CURRENCYMODEL_PLUGIN_H

#include <QQmlExtensionPlugin>

class CurrencyModelPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // CURRENCYMODEL_PLUGIN_H

