clear
clc
close all

%Leemos el txt y lo guardamos en una variable
fileID = fopen("datos.txt","r");
formato = '%c';
A = fscanf(fileID,formato);
%El ciclo se detiene cuando acaba de leer todo el txt
%% Capturamos a0
acero = [];
i = 1;
while(A(i) ~= ',') 
    acero = cat(2,acero,A(i));
    i = i + 1;
end
a0 = str2double(acero);
%%------------------------
%% Capturamos las an
i = i + 3;
aenes = [];
while(A(i) ~= '@')
    acero = [];
    while(A(i) ~= ',')
        acero = cat(2,acero,A(i));
        i = i + 1;
    end
    aenes = cat(2,aenes,str2double(acero));
    i = i + 1;
end
i = i + 1;
%%------------------
%% Capturamos las bn
i = i + 1;
disp(A(i));
benes = [];
while(A(i) ~= '@')
    acero = [];
    while(A(i) ~= ',')
        acero = cat(2,acero,A(i));
        i = i + 1;
    end
    benes = cat(2,benes,str2double(acero));
    i = i + 1;
end
i = i + 1;
%%------------------
%% Capturamos la frecuencia
i = i + 1;
acero = [];
while(i <= length(A))
    acero = cat(2,acero,A(i));
    i = i + 1;
end
w0 = str2double(acero);
%%-------------------------
%% Generamos el vector señal
t = 0:1/44100:2*pi;
sum_a = zeros(1,length(t));
for i = 1:1:length(aenes)
    sum_a = sum_a + (aenes(i)*cos(i*w0*t));
end
sum_b = zeros(1,length(t));
for i = 1:1:length(benes)
    sum_b = sum_b + (benes(i)*sin(i*w0*t));
end
sum = a0 + sum_a + sum_b;
%%------------------

%% Graficamos la señal
plot(t,sum);
%%--------------------