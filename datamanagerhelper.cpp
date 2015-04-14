#include "datamanagerhelper.h"
#include "placesdatamanager.h"

#include <QVariant>
#include <QJson/Parser>

QVariant DataManagerHelper::
parseJsonData(const QVariant & data)
{
    QJson::Parser parser;
    bool ok;

    QString strData( data.toString() );

#if QT_VERSION >= 0x050000
        // Qt5 code
    QByteArray arr( strData.toUtf8() );
#else
        // Qt4 code
    QByteArray arr( strData.toLatin1() );
#endif


    QVariant result = parser.parse(arr, & ok);

    if( ! ok ) {
        manager->errorOccured( QString("Cannot convert to QJson object:\n%1").arg(strData.left(32)).append("\n...") );
        return QVariant();
    }

    return result;
}

void DataManagerAutocompleter::
evalData(const QVariant & data)
{
    QVariant parsedJson = parseJsonData(data);
    QVariant predictions = parsedJson.toMap()["predictions"];
    if( predictions.isValid() ) manager->autocompleteData( predictions );
}

void DataManagerSearch::
evalData(const QVariant & data)
{
    QVariant parsedJson = parseJsonData(data);
    QVariant results = parsedJson.toMap()["results"];
    if( results.isValid() ) manager->findedPlaces( results );
}

void DataManagerPlaceDetails::
evalData(const QVariant & data)
{
    QVariant parsedJson = parseJsonData(data);
    if( parsedJson.isValid() ) manager->placeDetails( parsedJson );
}

void DataManagerCheckStatus::
evalData(const QVariant & data)
{
    QVariant parsedJson = parseJsonData(data);
    manager->requestStatus( m_operation, parsedJson );
}
