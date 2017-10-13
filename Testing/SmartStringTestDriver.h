//
// Created by molberding on 9/18/2017.
//

#ifndef UTILITYCODE_SMARTSTRINGTESTDRIVER_H
#define UTILITYCODE_SMARTSTRINGTESTDRIVER_H

#include "../DataTypes/SmartString.h"
#include "TestDriver.h"
#include <iostream>
#include <string>

using namespace smart_string;

class SmartStringTestDriver : public TestDriver {
private:

public:
    SmartStringTestDriver() {
        init("Smart String");
    };

    void testConstructors() {
        SmartString defaultConstructor;
        assert(0, defaultConstructor.length());
        SmartString charStarConstructor("charStarConstructor");
        assert(std::string("charStarConstructor"), charStarConstructor.str());
        SmartString charConstructor('c');
        assert('c', charConstructor[0]);
        std::string var = "stringConstructor";
        SmartString stringConstructor(var);
        assert(var, stringConstructor.str());
        SmartString fillConstructor(5, 'f');
        assert(std::string("fffff"), fillConstructor.str());
        int count = 0;
        char* tempFill = fillConstructor.c_str();
        while(tempFill[count++] != '\0') { }
        assert(6, count);
        delete tempFill;
        SmartString copyConstructor = fillConstructor;
        assert(copyConstructor.str(), fillConstructor.str());
        copyConstructor = stringConstructor;
        assert(copyConstructor.str(), stringConstructor.str());
        fillConstructor = "operator=";
        assert(std::string("operator="), fillConstructor.str());
        charConstructor = var;
        assert(var, charConstructor.str());
    }

    void testAppendPrepend() {
        SmartString temp;
        temp.append('1');
        assert(std::string("1"), temp.str());
        temp.append("23");
        assert(std::string("123"), temp.str());
        std::string var = "456";
        temp.append(var);
        assert(std::string("123456"), temp.str());
        SmartString smart = "789";
        temp.append(smart);
        assert(std::string("123456789"), temp.str());
        temp.prepend('0');
        assert(std::string("0123456789"), temp.str());
        temp.prepend("789");
        assert(std::string("7890123456789"), temp.str());
        temp.prepend(var);
        assert(std::string("4567890123456789"), temp.str());
        smart = "123";
        temp.prepend(smart);
        assert(std::string("1234567890123456789"), temp.str());

        temp = "";
        temp.append(1.0, 1);
        assert(std::string("1.0"), temp.str());
        temp.append(", ").append(-2.123456, 6);
        assert(std::string("1.0, -2.123456"), temp.str());
        temp.prepend(", ").prepend(-105.12345);
        assert(std::string("-105.12345, 1.0, -2.123456"), temp.str());
    }

    void testOperators() {
        SmartString temp = "1";
        temp << "234" << "5";
        assert(std::string("12345"), temp.str());
        temp << '6';
        assert(std::string("123456"), temp.str());
        std::string var = "789";
        temp << var;
        assert(std::string("123456789"), temp.str());

        temp = "2";
        temp.prepend('1').append("345").prepend("0");
        assert(std::string("012345"), temp.str());

        temp = "1";
        temp += "2";
        assert(std::string("12"), temp.str());

        temp = temp + "3" + '4';
        assert(std::string("1234"), temp.str());

        temp = "5" + temp;
        assert(std::string("51234"), temp.str());

        temp = var + temp;
        assert(std::string("78951234"), temp.str());

        assert(true, temp.contains("123"));
        assert(4, temp.findSubstring("123"));
    }

    void testReplaceAndFormat() {
        SmartString temp = "78951234";
        temp.replace("789", "123");
        assert(std::string("12351234"), temp.str());

        temp.replaceAll("123", "x");
        assert(std::string("x5x4"), temp.str());

        temp = "1";
        temp << 2345;
        assert(std::string("12345"), temp.str());

        SmartString formatString = "{0} {1} {2} {0}";
        formatString.format(3, "a", "b", "c");
        assert(std::string("a b c a"), formatString.str());

        std::string str = (std::string) temp;
        assert(std::string("12345"), str);

        char* charStr = (char*) temp;
        assert(temp.str(), std::string(charStr));

        formatString = "{0} {1} {2} {0}";
        str = formatString.getFormatted<std::string>(3, "a", "b", "c");
        assert(std::string("a b c a"), str);
        charStr = formatString.getFormatted<char *>(3, "a", "b", "c");
        assert(std::string("a b c a"), std::string(charStr));
        temp = formatString.getFormatted<SmartString>(3, "a", "b", "c");
        assert(std::string("a b c a"), temp.str());

        str = formatString.getFormatted<std::string>("a", "b", "c");
        assert(std::string("a b c a"), str);
        charStr = formatString.getFormatted<char *>("a", "b", "c");
        assert(std::string("a b c a"), std::string(charStr));
        temp = formatString.getFormatted<SmartString>("a", "b", "c");
        assert(std::string("a b c a"), temp.str());
    }

    void testRemove() {
        SmartString temp = "123411";
        temp.remove("23");
        assert(std::string("1411"), temp.str());
        temp.removeAll("1");
        assert(std::string("4"), temp.str());
        temp = "123456";
        temp.remove(0, 0);
        assert(std::string("23456"), temp.str());
        temp.remove(0, 2);
        assert(std::string("56"), temp.str());
        temp.remove(1,1);
        assert(std::string("5"), temp.str());
    }

    void testSubstrings() {
        SmartString temp("1212121");
        assert(4, temp.count("1"));
        assert(3, temp.count("12"));
        temp = "12314516";
        assert(std::string("1"), temp.getSubstring<std::string>(0,0));
        std::vector<SmartString> list = temp.split<SmartString>("1");
        assert(4, (int) list.size());
        assert(std::string(""), list[0].str());
        assert(std::string("23"), list[1].str());
        assert(std::string("45"), list[2].str());
        assert(std::string("6"), list[3].str());
        temp = "this is a multi-line piece of text.\n";
        temp.append("it's way longer than it has any right to be.\n");
        temp.append("....that's what she said.\n");
        list = temp.split<SmartString>("\n");
        assert(3, (int) list.size());
        assert(std::string("this is a multi-line piece of text."), list[0].str());
        assert(std::string("it's way longer than it has any right to be."), list[1].str());
        assert(std::string("....that's what she said."), list[2].str());
        temp = "";
        temp = SmartString::join(list, "\n");
        assert(std::string("this is a multi-line piece of text.\nit's way longer than it has any right to be.\n....that's what she said."), temp.str());
    }

    void run() {
        testConstructors();
        testAppendPrepend();
        testOperators();
        testReplaceAndFormat();
        testRemove();
        testSubstrings();
    }
};
#endif //UTILITYCODE_SMARTSTRINGTESTDRIVER_H
