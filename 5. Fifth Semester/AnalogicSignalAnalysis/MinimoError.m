clear
clc

% frecuencia de muestreo
fs = 50;

%Vector de muestreo
t = 0:1/fs:2*pi;

%Señal original (cuadrada)
s = square(t);

%Vector que le da valores a las constantes que voy a variar en cada ciclo
C = 0:0.01:3;

C1 = zeros(1,length(C)*length(C));
C2 = zeros(1,length(C)*length(C));
E = zeros(1,length(C)*length(C));

%Iterador sobre los vectores que tienen las señales finales
j = 1;

MinErr = 5000000000;

%Ciclos para variar las constantes
for const1 = 1:1:length(C)
    for const2 = 1:1:length(C)
        % Realizo una integración numérica de la función que utilizo para
        % aproximarme a la original
        f = (C(const1)*sin(t) + C(const2)*sin(3*t));
        fe = s - f;
        f = sum(fe.*fe)/length(t);
        C1(j) = C(const1);
        C2(j) = C(const2);
        E(j) = f;
        if f < MinErr
            MinErr = f;
            C1minerr = C(const1);
            C2minerr = C(const2);
        end
        j = j + 1;
    end
end

%plot3(C1,C2,E,'-b',C1minerr,C2minerr,MinErr,'or');
%mesh(C1,C2,E);
[C1,C2] = meshgrid(0:0.01:3);
surface(C1,C2,E,'FaceAlpha',0.5);
view(3);
xlabel("C1");
ylabel("C2");
zlabel("E");
%v = strcat("Minimo Error: E(", string(C1minerr), ",", string(C2minerr), ") = ",string(MinErr));
%text(C1minerr,C2minerr,v);