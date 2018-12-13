plot3(0,0,0,'o');
hold on
plot3(0,0,-1,'o');
plot3(0,6,-1,'o');
plot3(0,6,0,'o');
plot3(0,8,0,'o');
X = [0 0 0 0 0];
Y = [0 0 6 6 8];
Z = [0 -1 -1 0 0];
plot3(X,Y,Z,'k-')

A = [0 0 0];
B = [0 0 -1];
C = [0 6 -1];
D = [0 6 0];
E = [0 8 0];
F = [0 0 0];
G = [0 12 0];
M = [A.',B.',C.',D.',E.'];
X = M(1,:);
Y = M(2,:);
Z = M(3,:);
plot3(X,Y,Z,'k-');
axis([-15 15 -15 15 -15 15]);

for theta1 = 0:20/360*pi:2*pi
    A1 = TRANS0_1(A,theta1);
    B1 = TRANS0_1(B,theta1);
    C1 = TRANS0_1(C,theta1);
    D1 = TRANS0_1(D,theta1);
    E1 = TRANS0_1(E,theta1);
    %F1 = TRANS0_1(F,theta1);
    M = [A1.',B1.',C1.',D1.',E1.'];
    X1 = M(1,:);
    Y1 = M(2,:);
    Z1 = M(3,:);
    
    
    for theta2 = 0:20/360*pi:2*pi
        F2 = TRANS1_2(F,theta2);
        G2 = TRANS1_2(G,theta2);
        F1 = TRANS0_1(F2,theta1);
        G1 = TRANS0_1(G2,theta1);
        %N = [F1.',G1.'];
        N = [G1.'];
        X2 = N(1,:);
        Y2 = N(2,:);
        Z2 = N(3,:);
        %plot3(X1,Y1,Z1,'r-');
        axis([-15 15 -15 15 -15 15]);
        hold on
        plot3(X2,Y2,Z2,'bo');
        %hold off
        pause(0.05)
    end
    
    
end

