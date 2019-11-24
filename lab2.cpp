/*
MIT License

Copyright (c) 2019 МГТУ им. Н.Э. Баумана, кафедра ИУ-6, Михаил Фетисов,

Программа-заготовка для лабораторной работы
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

using namespace std;

class IOutput
{
public:
    virtual ~IOutput() = default;

    virtual string getOutputString() const = 0;
};

class Order : public IOutput
{
public:
    Order() = delete;
    Order & operator = (const Order & p) = delete;

    Order(uint16_t order_number, const string & courier_name, const string & address, const string & good_name, uint16_t total)
      : _order_number(order_number), _courier_name(courier_name), _address(address), _good_name(good_name), _total(total)
    {
    }

    uint16_t       getOrderNumber() const { return _order_number; }
    const string & getCourierName() const { return _courier_name; }
    const string & getAddress() const { return _address; }
    const string & getGoodName() { return _good_name; }
    uint16_t getTotal() const { return _total; }


    virtual string getOutputString() const override
    {
        return to_string(_order_number) + ", " + _courier_name + ", " + _address + ", " + _good_name + ", " + to_string(_total);
    }



private:
    uint16_t _order_number;
    string _courier_name;
    string _address;
    string _good_name;
    uint16_t _total;
};

class NullOrder : public IOutput
{
  virtual string getOutputString() const override
  {
    return "Null Object";
  }

};



int main(int argc, char * argv[])
{
    multimap<string,unique_ptr<IOutput>> crew;

    crew.insert({"VN-RU", make_unique<Order>(1, "Ivan", "Books", "Moscow", 500)});
    crew.insert({"VN-RU", make_unique<Order>(2, "Shasa", "Glasses", "Saint", 1000)});
    crew.insert({"VN-RU", make_unique<Order>(3, "Bulgaru", "Pants", "Tula", 700)});
    crew.insert({"RU-EU", make_unique<Order>(4, "Michael", "Laptop", "London", 60000)});
    crew.insert({"EU-RU", make_unique<Order>(5, "Lisa", "Clothes", "Volgorad", 1300)});

    set<std::string> key_set(argv + 1, argv + argc);

    if (key_set.empty())
    {
        for(const auto & [k,o] : crew)
            cout << "\"" << k << "\": " << o->getOutputString() << endl;
    }
    else
        for(auto key : key_set)
        {

              auto [begin, end] = crew.equal_range(key);

              if (begin == end) {
                IOutput * o = new NullOrder();

                cout << o->getOutputString() << endl;

                delete o;
                //cout << key << endl;
             }
              else {
                for(auto it=begin; it != end; ++it)
                    cout << "\"" << key << "\": " << it->second->getOutputString() << endl;
             }
        }
    return 0;
}
