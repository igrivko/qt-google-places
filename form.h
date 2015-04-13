#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QModelIndex>
#include "placedialog.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    
public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    
private slots:
    void errorOccured(const QString & error);
    void editSettings();

    void attachJsObjects();

    void loadHtmlPage(const QString & apiKey);
    void initMap(bool);

    void searchTextChanged();
    void searchPlace();
    void findedPlaces(const QVariant & data);
    void autocompleteData(const QVariant & data);
    void autocompleteItemDoubleClicked(const QModelIndex &);
    void gotoPlace(const QModelIndex &);

    void requestPlaceInformation(const QString & reference);
    void showPlaceInformation(const QVariant & info);

    void requestStatus(const QString & operation, const QVariant & value);

    void addPlace();
    void addEvent(const QString & reference);

    void gotoPlaceByCoordinate(const QString & place);

private:
    void setupSearchOptionComboboxes();

private:
    Ui::Form * ui;
    class PlacesDataManager * m_pDataManager;
    class PlacesJsManager * m_pJsManager;

    class VariantListModel * m_pAutocompletModel;
    class VariantListModel * m_pPlacesModel;

    QString m_strApiKey;
    QString m_organizationName;
    QString m_appName;
    QString m_clickedAddress;
    QString m_clickedCoordinate;
    PlaceDialog *m_placeDialog;
};

#endif // FORM_H
