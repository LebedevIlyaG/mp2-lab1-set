// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cmath>

//Fake variables used as placeholders in tests
//static const int FAKE_INT = -1;
//static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
  if (len < 1)
    throw "invalid length";
  BitLen = len;
  MemLen = ceil((double)(len) / (sizeof(TELEM) * 8));
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
    pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
  MemLen = bf.MemLen;
  BitLen = bf.BitLen;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
	pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n < 0 || n > BitLen)
	throw "invalid length";
  return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if (n < 0 || n > BitLen)
	throw "invalid length";
  return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if (n < 0 || n > BitLen)
	throw "invalid length";
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if (n < 0 || n > BitLen)
	throw "invalid length";
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n < 0 || n > BitLen)
	throw "invalid length";
  return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
  if (this == &bf)
	return *this;
  MemLen = bf.MemLen;
  BitLen = bf.BitLen;
  delete[] pMem;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
	pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
  if (BitLen != bf.BitLen)
	return 0;
  for (int i = 0; i < MemLen; i++)
  {
    if (pMem[i] == bf.pMem[i])
      return 1;
  }
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
  return !(this == &bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
  int max = BitLen;
  if (bf.BitLen > BitLen)
	max = bf.BitLen;
  TBitField res(max);
  for (int i = 0; i < MemLen; i++)
	res.pMem[i] |= bf.pMem[i];
  return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
  int max = BitLen;
  if (bf.BitLen > BitLen)
	max = bf.BitLen;
  TBitField res(max);
  for (int i = 0; i < MemLen; i++)
	res.pMem[i] &= bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(*this);
  for (int i = 0; i < MemLen; i++)
	res.pMem[i] = ~pMem[i];
  return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
  for (int i = 0; i < bf.BitLen; i++)
  {
    int tmp;
    istr >> tmp;
    if (tmp == 0) 
      bf.ClrBit(i);
    else
	  bf.SetBit(i); //?
  }
  return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
  ostr << bf.BitLen;
  for (int i = 0; i < bf.BitLen; i++) 
	ostr << 0;
  return ostr;
}
