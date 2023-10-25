

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int k = n >> 5;
	return k;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int k = n >> 5;
	int pos = n & 31;
	return pos;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] |= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
	{
		int k = pMem[GetMemIndex(n)] & GetMemMask(n);
		return k;
	}
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL)
			delete(pMem);
		pMem = new TELEM[MemLen];
	};
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		};
	};
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (pMem[i] = bf.pMem[i])
			  return 0;
		}
  }
	else
		return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return (this -> operator==(bf));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}
	TBitField temp(len);
	for (int i = 0; i < MemLen; i++)
		temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		temp.pMem[i] &= bf.pMem[i];
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.MemLen; i++)
	{
		if (bf.GetBit(i)) {
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
    return ostr;
}
