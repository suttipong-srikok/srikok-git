#include "settings.h"
#include <QSettings>
#include <QGroupBox>
#include <QFileDialog>
#include <QStandardPaths>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
    , m_tabWidget(nullptr)
    , m_userNameEdit(nullptr)
    , m_userEmailEdit(nullptr)
    , m_gitPathEdit(nullptr)
    , m_saveButton(nullptr)
    , m_cancelButton(nullptr)
{
    setupUI();
    loadSettings();
}

void Settings::setupUI()
{
    setWindowTitle("Settings");
    setModal(true);
    resize(400, 300);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    m_tabWidget = new QTabWidget;
    
    QWidget *generalTab = new QWidget;
    QVBoxLayout *generalLayout = new QVBoxLayout(generalTab);
    
    QGroupBox *userGroup = new QGroupBox("User Information");
    QVBoxLayout *userLayout = new QVBoxLayout(userGroup);
    
    QLabel *nameLabel = new QLabel("Name:");
    m_userNameEdit = new QLineEdit;
    
    QLabel *emailLabel = new QLabel("Email:");
    m_userEmailEdit = new QLineEdit;
    
    userLayout->addWidget(nameLabel);
    userLayout->addWidget(m_userNameEdit);
    userLayout->addWidget(emailLabel);
    userLayout->addWidget(m_userEmailEdit);
    
    QGroupBox *pathGroup = new QGroupBox("Git Path");
    QVBoxLayout *pathLayout = new QVBoxLayout(pathGroup);
    
    QLabel *gitLabel = new QLabel("Git Executable:");
    m_gitPathEdit = new QLineEdit;
    m_gitPathEdit->setText("git");
    
    pathLayout->addWidget(gitLabel);
    pathLayout->addWidget(m_gitPathEdit);
    
    generalLayout->addWidget(userGroup);
    generalLayout->addWidget(pathGroup);
    generalLayout->addStretch();
    
    m_tabWidget->addTab(generalTab, "General");
    
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_saveButton = new QPushButton("Save");
    m_cancelButton = new QPushButton("Cancel");
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_cancelButton);
    
    layout->addWidget(m_tabWidget);
    layout->addLayout(buttonLayout);
    
    connect(m_saveButton, &QPushButton::clicked, this, &Settings::saveSettings);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void Settings::saveSettings()
{
    QSettings settings;
    settings.setValue("user/name", m_userNameEdit->text());
    settings.setValue("user/email", m_userEmailEdit->text());
    settings.setValue("git/path", m_gitPathEdit->text());
    
    accept();
}

void Settings::loadSettings()
{
    QSettings settings;
    m_userNameEdit->setText(settings.value("user/name").toString());
    m_userEmailEdit->setText(settings.value("user/email").toString());
    m_gitPathEdit->setText(settings.value("git/path", "git").toString());
}