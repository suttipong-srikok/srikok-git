#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);

private slots:
    void saveSettings();
    void loadSettings();

private:
    void setupUI();
    
    QTabWidget *m_tabWidget;
    QLineEdit *m_userNameEdit;
    QLineEdit *m_userEmailEdit;
    QLineEdit *m_gitPathEdit;
    QPushButton *m_saveButton;
    QPushButton *m_cancelButton;
};

#endif // SETTINGS_H