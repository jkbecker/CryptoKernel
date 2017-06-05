/*  CryptoCurrency - An example crypto-currency using the CryptoKernel library as a base
    Copyright (C) 2016  James Lovejoy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef JSONRPC_CPP_STUB_CRYPTOSERVER_H_
#define JSONRPC_CPP_STUB_CRYPTOSERVER_H_

#include <jsonrpccpp/server.h>

#include "wallet.h"

class CryptoRPCServer : public jsonrpc::AbstractServer<CryptoRPCServer>
{
    public:
        CryptoRPCServer(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2) : jsonrpc::AbstractServer<CryptoRPCServer>(conn, type)
        {
            this->bindAndAddMethod(jsonrpc::Procedure("getinfo", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT,  NULL), &CryptoRPCServer::getinfoI);
            this->bindAndAddMethod(jsonrpc::Procedure("account", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "account",jsonrpc::JSON_STRING, NULL), &CryptoRPCServer::accountI);
            this->bindAndAddMethod(jsonrpc::Procedure("sendtoaddress", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_BOOLEAN, "address",jsonrpc::JSON_STRING,"amount",jsonrpc::JSON_REAL,"fee",jsonrpc::JSON_REAL, NULL), &CryptoRPCServer::sendtoaddressI);
            this->bindAndAddMethod(jsonrpc::Procedure("sendrawtransaction", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_BOOLEAN, "transaction",jsonrpc::JSON_OBJECT, NULL), &CryptoRPCServer::sendrawtransactionI);
            this->bindAndAddMethod(jsonrpc::Procedure("listaccounts", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, NULL), &CryptoRPCServer::listaccountsI);
            this->bindAndAddMethod(jsonrpc::Procedure("listunspentoutputs", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "account",jsonrpc::JSON_STRING, NULL), &CryptoRPCServer::listunspentoutputsI);
            this->bindAndAddMethod(jsonrpc::Procedure("compilecontract", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "code",jsonrpc::JSON_STRING, NULL), &CryptoRPCServer::compilecontractI);
            this->bindAndAddMethod(jsonrpc::Procedure("calculateoutputid", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_STRING, "output",jsonrpc::JSON_OBJECT, NULL), &CryptoRPCServer::calculateoutputidI);
            this->bindAndAddMethod(jsonrpc::Procedure("signtransaction", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "transaction",jsonrpc::JSON_OBJECT, NULL), &CryptoRPCServer::signtransactionI);
            this->bindAndAddMethod(jsonrpc::Procedure("listtransactions", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, NULL), &CryptoRPCServer::listtransactionsI);
            this->bindAndAddMethod(jsonrpc::Procedure("getblockbyheight", jsonrpc::PARAMS_BY_NAME, jsonrpc::JSON_OBJECT, "height", jsonrpc::JSON_INTEGER, NULL), &CryptoRPCServer::getblockbyheightI);
        }

        inline virtual void getinfoI(const Json::Value &request, Json::Value &response)
        {
            response = this->getinfo();
        }
        inline virtual void accountI(const Json::Value &request, Json::Value &response)
        {
            response = this->account(request["account"].asString());
        }
        inline virtual void sendtoaddressI(const Json::Value &request, Json::Value &response)
        {
            response = this->sendtoaddress(request["address"].asString(), request["amount"].asDouble(), request["fee"].asDouble());
        }
        inline virtual void sendrawtransactionI(const Json::Value &request, Json::Value &response)
        {
            response = this->sendrawtransaction(request["transaction"]);
        }
        inline virtual void listaccountsI(const Json::Value &request, Json::Value &response)
        {
            response = this->listaccounts();
        }
        inline virtual void listunspentoutputsI(const Json::Value &request, Json::Value &response)
        {
            response = this->listunspentoutputs(request["account"].asString());
        }
        inline virtual void compilecontractI(const Json::Value &request, Json::Value &response)
        {
            response = this->compilecontract(request["code"].asString());
        }
        inline virtual void calculateoutputidI(const Json::Value &request, Json::Value &response)
        {
            response = this->calculateoutputid(request["output"]);
        }
        inline virtual void signtransactionI(const Json::Value &request, Json::Value &response)
        {
            response = this->signtransaction(request["transaction"]);
        }
        inline virtual void listtransactionsI(const Json::Value &request, Json::Value &response)
        {
            response = this->listtransactions();
        }
        inline virtual void getblockbyheightI(const Json::Value &request, Json::Value &response)
        {
            response = this->getblockbyheight(request["height"].asUInt64());
        }
        virtual Json::Value getinfo() = 0;
        virtual Json::Value account(const std::string& account) = 0;
        virtual bool sendtoaddress(const std::string& address, double amount, double fee) = 0;
        virtual bool sendrawtransaction(const Json::Value tx) = 0;
        virtual Json::Value listaccounts() = 0;
        virtual Json::Value listunspentoutputs(const std::string& account) = 0;
        virtual std::string compilecontract(const std::string& code) = 0;
        virtual std::string calculateoutputid(const Json::Value output) = 0;
        virtual Json::Value signtransaction(const Json::Value tx) = 0;
        virtual Json::Value listtransactions() = 0;
        virtual Json::Value getblockbyheight(const uint64_t height) = 0;
};

class CryptoServer : public CryptoRPCServer
{
    public:
        CryptoServer(jsonrpc::AbstractServerConnector &connector);

        virtual Json::Value getinfo();
        virtual Json::Value account(const std::string& account);
        virtual bool sendtoaddress(const std::string& address, double amount, double fee);
        virtual bool sendrawtransaction(const Json::Value tx);
        void setWallet(CryptoCurrency::Wallet* Wallet, CryptoKernel::Blockchain* Blockchain, CryptoKernel::Network* Network);
        virtual Json::Value listaccounts();
        virtual Json::Value listunspentoutputs(const std::string& account);
        virtual std::string compilecontract(const std::string& code);
        virtual std::string calculateoutputid(const Json::Value output);
        virtual Json::Value signtransaction(const Json::Value tx);
        virtual Json::Value listtransactions();
        virtual Json::Value getblockbyheight(const uint64_t height);

    private:
        CryptoCurrency::Wallet* wallet;
        CryptoKernel::Blockchain* blockchain;
        CryptoKernel::Network* network;
};


#endif //JSONRPC_CPP_STUB_CRYPTOSERVER_H_
