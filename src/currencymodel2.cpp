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

#include <QDebug>
#include "currencymodel2.h"

bool lcComp(QLocale a, QLocale b) {
    return QLocale::countryToString(a.country()).compare(QLocale::countryToString(b.country())) < 0;
}

CurrencyModel2::CurrencyModel2(QObject *parent) :
    QAbstractListModel(parent)
{
    //setRoleNames(m_prototype->roleNames());
    QList<QString> codes;

    QLocale sys = QLocale::system();
    //QList<QLocale> locales = QLocale::matchingLocales(sys.language(), sys.script(), QLocale::AnyCountry);
    QList<QLocale> locales = QLocale::matchingLocales(QLocale::AnyLanguage, sys.script(), QLocale::AnyCountry);
    qSort(locales.begin(), locales.end(), lcComp);

    int i = 0;
    foreach (QLocale l, locales) {
        if(codes.contains(l.currencySymbol(QLocale::CurrencyIsoCode)) || l.currencySymbol(QLocale::CurrencyIsoCode) == "") {
            continue;
        }
        codes << l.currencySymbol(QLocale::CurrencyIsoCode);
        i++;
        this->appendRow(new CurrencyItem2(QLocale::countryToString(l.country()), l));
        qDebug() << QLocale::countryToString(l.country()) << l.currencySymbol(QLocale::CurrencyIsoCode);
    }
    qDebug() << i << "languages";

}

int CurrencyModel2::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant CurrencyModel2::data(const QModelIndex &index, int role) const
{
    qDebug() << "role" << role;

    if(index.row() < 0 || index.row() >= m_list.size()) {
        return QVariant();
    }

    QVariant v;
    v.setValue(static_cast<QObject *>(m_list[index.row()]));
    return v;
    //return m_list.at(index.row())->data(role);
}

CurrencyModel2::~CurrencyModel2() {
    //delete m_prototype;
    clear();
}

QHash<int, QByteArray> CurrencyModel2::roleNames() const
{
    static QHash<int, QByteArray> roles;
    if (roles.isEmpty())
        roles[0] = "currency";
    return roles;
}

void CurrencyModel2::appendRow(CurrencyItem2 *item)
{
  appendRows(QList<CurrencyItem2*>() << item);
}

void CurrencyModel2::appendRows(const QList<CurrencyItem2 *> &items)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
  foreach(CurrencyItem2 *item, items) {
    connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
    m_list.append(item);
  }
  endInsertRows();
}

void CurrencyModel2::insertRow(int row, CurrencyItem2 *item)
{
  beginInsertRows(QModelIndex(), row, row);
  connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
  m_list.insert(row, item);
  endInsertRows();
}

void CurrencyModel2::handleItemChange()
{
  CurrencyItem2* item = static_cast<CurrencyItem2*>(sender());
  QModelIndex index = indexFromItem(item);
  if(index.isValid())
    emit dataChanged(index, index);
}

//CurrencyModel2 * CurrencyModel2::find(const QString &id) const
//{
//  foreach(CurrencyItem2* item, m_list) {
//    if(item->id() == id) return item;
//  }
//  return 0;
//}

QModelIndex CurrencyModel2::indexFromItem(const CurrencyItem2 *item) const
{
  Q_ASSERT(item);
  for(int row=0; row<m_list.size(); ++row) {
    if(m_list.at(row) == item) return index(row);
  }
  return QModelIndex();
}

void CurrencyModel2::clear()
{
  qDeleteAll(m_list);
  m_list.clear();
}

bool CurrencyModel2::removeRow(int row, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  if(row < 0 || row >= m_list.size()) return false;
  beginRemoveRows(QModelIndex(), row, row);
  delete m_list.takeAt(row);
  endRemoveRows();
  return true;
}

bool CurrencyModel2::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  if(row < 0 || (row+count) >= m_list.size()) return false;
  beginRemoveRows(QModelIndex(), row, row+count-1);
  for(int i=0; i<count; ++i) {
    delete m_list.takeAt(row);
  }
  endRemoveRows();
  return true;
}

CurrencyItem2 * CurrencyModel2::takeRow(int row)
{
  beginRemoveRows(QModelIndex(), row, row);
  CurrencyItem2* item = m_list.takeAt(row);
  endRemoveRows();
  return item;
}
