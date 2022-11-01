#pragma once
#include "NODE.H"

void Create(bool& exit);//Создать БД

void VivSP(bool& exit);//Вывести на экран список существующих БД

void Delete(bool& exit);//Удалить БД

void Rename(bool& exit);//Переименовать БД

void Open(bool& exit);//Открыть БД

void Add(bool& exit);//Добавить запись в БД

void RedactZap(bool& exit);//Редактировать запись в БД

void DeleteZap(bool& exit);//Удалить запись из БД

void VivZap(bool& exit);//Вывести на экран записи из БД

void SortZap(bool& exit);//Сортировать записи в БД

void Vibrk(bool& exit);//Совершить выборку записей в БД

void SaveVibrk(bool& exit);//Сохранить выборку в новой БД

void Kolneudstud(bool& exit);

void Poisk(bool& exit);