#!/bin/sh
m=0
until test $m = 4
do
 echo "МЕНЮ"
 echo "------------------------------"
 echo "1) Информация о авторе"
 echo "2) Копирование файлов из указанного места в заданное"
 echo "3) Очистить каталог с подтверждением"
 echo "4) Выход"
 echo "Выберите пункт меню:"
 read m

 if [ $m = 1 ]
  then echo "Бут-Гусаим Данила Григорьевич"
   echo "ИТИ-11"
   echo "Пункт 1 - Информаци о авторе и пунктах меню"
   echo "Пункт 2 - Копирование файлов из указанного каталога в заданный каталог"
   echo "Пункт 3 - Очистка заданного каталога"
   echo "Пункт 4 - Завершени работы"
 fi

 if [ $m = 2 ]
  then echo "Из каталога:"
   read start
   if [ -d $start ]
    then echo "В каталог:"
     read finish
     if [ -d $finish ]
      then echo "Данные введены правильно"
       n=0
       for file in $start/*
	do
         if [ -f "$file" ]
	  then cp "$file" $finish
	  n=`expr $n + 1`
	 fi	
        done 
        echo "Скопировано $n файлов"
      else echo "Такой каталог не найден!"
     fi  
    else echo "Такой каталог не найден!"
   fi
 fi
 
 if [ $m = 3 ]
  then echo "Введите имя каталога кторый нужно очистить"
   read area
   if [ -d $area ]
    then echo "Данный котолог найден"
     for obj in $area/*
	do
         rm -i -r "$obj" 
        done 
    else echo "Такой каталог не найден!"
   fi
 fi 
 
 if [ $m = 4 ]
  then echo "Конец сеанса"
 fi
	
done