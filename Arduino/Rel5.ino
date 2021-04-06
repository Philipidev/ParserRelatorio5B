int ledRed = 13;
int ledYel = 12;
int ledGre = 11;
int ledBlu = 10;
char memoria[100];
int posMemAtual = 2;

void setup()
{
    Serial.begin(9600);
    pinMode(ledRed, OUTPUT);
    pinMode(ledYel, OUTPUT);
    pinMode(ledGre, OUTPUT);
    pinMode(ledBlu, OUTPUT);

    Serial.print("X - Y - W....");
    Serial.println();

    for (int i = 0; i < 100; i++)
    {
        memoria[i] = '\0';
    }
}

String InverterBinario(String item)
{
    String res = item;
    for (int i = 0; i < 4; i++)
    {
        if (item[i] == '0')
            res[i] = '1';
        else
            res[i] = '0';
    }
    return res;
}

String Or(String item1, String item2)
{
    String res = item1;
    for (int i = 0; i < 4; i++)
    {
        if (item1[i] == '0' & item2[i] == '0')
            res[i] = '0';
        else
            res[i] = '1';
    }
    return res;
}

String And(String item1, String item2)
{
    String res = item1;
    for (int i = 0; i < 4; i++)
    {
        if (item1[i] == '1' & item2[i] == '1')
            res[i] = '1';
        else
            res[i] = '0';
    }
    return res;
}

String Xor(String item1, String item2)
{
    String res = item1;
    for (int i = 0; i < 4; i++)
    {
        if (item1[i] == '0' & item2[i] == '1')
            res[i] = '1';
        else if (item1[i] == '1' & item2[i] == '0')
            res[i] = '1';
        else
            res[i] = '0';
    }
    return res;
}

String ParseHex(char item)
{
    if (item == '0')
        return "0000";
    if (item == '1')
        return "0001";
    if (item == '2')
        return "0010";
    if (item == '3')
        return "0011";
    if (item == '4')
        return "0011";
    if (item == '5')
        return "0101";
    if (item == '6')
        return "0110";
    if (item == '7')
        return "0111";
    if (item == '8')
        return "1000";
    if (item == '9')
        return "1001";
    if (item == 'A')
        return "1010";
    if (item == 'B')
        return "1011";
    if (item == 'C')
        return "1100";
    if (item == 'D')
        return "1101";
    if (item == 'E')
        return "1110";
    if (item == 'F')
        return "1111";
    return "0000";
}

String ParseMnemonico(char op)
{
    if (op == '0')
        return InverterBinario(ParseHex(memoria[0]));
    else if (op == '1')
        return InverterBinario(Or(ParseHex(memoria[0]), ParseHex(memoria[1])));
    else if (op == '2')
        return And(InverterBinario(ParseHex(memoria[0])), ParseHex(memoria[1]));
    else if (op == '3')
        return "0000";
    else if (op == '4')
        return InverterBinario(And(ParseHex(memoria[0]), ParseHex(memoria[1])));
    else if (op == '5')
        return InverterBinario(ParseHex(memoria[1]));
    else if (op == '6')
        return Xor(ParseHex(memoria[0]), ParseHex(memoria[1]));
    else if (op == '7')
        return And(ParseHex(memoria[0]), InverterBinario(ParseHex(memoria[1])));
    else if (op == '8')
        return Or(InverterBinario(ParseHex(memoria[0])), ParseHex(memoria[1]));
    else if (op == '9')
        return InverterBinario(Xor(ParseHex(memoria[0]), ParseHex(memoria[1])));
    else if (op == 'A')
        return ParseHex(memoria[1]);
    else if (op == 'B')
        return And(ParseHex(memoria[0]), ParseHex(memoria[1]));
    else if (op == 'C')
        return "1111";
    else if (op == 'D')
        return Or(ParseHex(memoria[0]), InverterBinario(ParseHex(memoria[1])));
    else if (op == 'E')
        return Or(ParseHex(memoria[0]), ParseHex(memoria[1]));
    else if (op == 'F')
        return ParseHex(memoria[0]);

    return "0000";
}

void ValorLed(String item)
{
    if (item[0] == '1')
        digitalWrite(ledRed, HIGH);
    else
        digitalWrite(ledRed, LOW);

    if (item[1] == '1')
        digitalWrite(ledYel, HIGH);
    else
        digitalWrite(ledYel, LOW);

    if (item[2] == '1')
        digitalWrite(ledGre, HIGH);
    else
        digitalWrite(ledGre, LOW);

    if (item[3] == '1')
        digitalWrite(ledBlu, HIGH);
    else
        digitalWrite(ledBlu, LOW);
}

void dump()
{
    for (int i = 0; i <= posMemAtual; i++)
    {
        if (i == 0 | i == 1)
            Serial.print(memoria[i]);
        else
            Serial.print(memoria[i]);
        if (i != posMemAtual)
            Serial.print(" - ");
    }
}

void loop()
{
    if (Serial.available() > 0)
    {
        String linha = Serial.readString();
        memoria[0] = linha[0];
        memoria[1] = linha[1];
        memoria[posMemAtual] = linha[2];
        //ToDo: memoria[W] = resposta do parse em Hexadecimal
        String resp = ParseMnemonico(linha[2]);

        dump();
        Serial.println();

        ValorLed(resp);
        posMemAtual++;
    }
}