/*
  Copyright (C) 2014 Thomas Tanghus <thomas@tanghus.net>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CYRRENCYITEM2_H
#define CYRRENCYITEM2_H

#include <QObject>
#include <QLocale>

#include "currencyitem2.h"

class CurrencyItem2 : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CurrencyItem2)

    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(QString country READ country)
    Q_PROPERTY(QString code READ code)

public:
    CurrencyItem2(QObject* parent = 0) : QObject(parent) {}
    explicit CurrencyItem2(const QString& title, const QLocale locale, QObject *parent = 0);
    virtual ~CurrencyItem2() {}
  //  virtual QString id() const = 0;

    enum Roles {
        //IdRole = Qt::UserRole + 1,
        CurrencyRole,
        TitleRole,
        CountryRole,
        CodeRole,
        LocaleRole
    };

    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    //inline int id() const {return m_id;}
    inline QString title() const {return m_title;}
    inline QString country() const {return QLocale::countryToString(m_locale.country());}
    inline QString code() const { return m_locale.currencySymbol(QLocale::CurrencyIsoCode);}
    inline QLocale locale() const {return m_locale;}
    
signals:
  void dataChanged();

public slots:

private:
    QString m_title;
    QLocale m_locale;
    
};

#endif // CYRRENCYITEM2_H
