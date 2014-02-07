/*
  Copyright (C) 2013 Thomas Tanghus
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

import QtQuick 2.0
import Sailfish.Silica 1.0

ComboBox {
    id: currencyCombo;

    signal activated(Item currency);

    property string currentCurrency;

    onCurrentCurrencyChanged: {
        console.log('Setting currency', currentCurrency, typeof currentCurrency, currentCurrency.length);
        if(typeof currentCurrency !== 'string' || currentCurrency.length !== 3) {
            console.log('Trying to set invalid currency', currentCurrency);
            return;
        }

        // Use the children directly from the model as the menu isn't populated yet
        var currencies = currencyModel.children;

        for(var i = 0; i < currencies.length; i++ ) {
            if(currencies[i].code === currentCurrency) {
                currentItem = currencies[i];
                return;
            }
        }
    }

    onCurrentIndexChanged: {
        console.log('currentIndex changed', currentIndex);
        var currency = currencyModel.children[currentIndex];
        currencyCombo.activated(currency);
        _updating = true;
        currentCurrency = currency.code;
        _updating = false;
    }

    menu: ContextMenu {
        id: contextMenu;
        Repeater {
             model: currencyModel
        }
        onActivated: {
            var currency = contextMenu.children[index];
            currencyCombo.activated(currency);
            _updating = true;
            currentCurrency = currency.code;
            _updating = false;
        }
    }

    CurrencyModel {
        id: currencyModel
    }
}
