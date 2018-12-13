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
axis([-15 15 -15 15 -15 15]);

A1 = [0 0 0];
B1 = [0 0 -1];
C1 = [0 6 -1];
D1 = [0 6 0];
E1 = [0 8 0];
F2 = [0 0 0];
G2 = [0 12 0];


for theta2 = 0:30/360*pi:2*pi
        F1 = TRANS1_2(F2,theta2);
        G1 = TRANS1_2(G2,theta2);

   for theta1 = 0:20/360*pi:2*pi
        A0 = TRANS0_1(A1,theta1);
        B0 = TRANS0_1(B1,theta1);
        C0 = TRANS0_1(C1,theta1);
        D0 = TRANS0_1(D1,theta1);
        E0 = TRANS0_1(E1,theta1);
        F0 = TRANS0_1(F1,theta1);
        G0 = TRANS0_1(G1,theta1);
        M = [A0.',B0.',C0.',D0.',E0.'];
        N = [F0.',G0.'];
        X2 = N(1,:);
        Y2 = N(2,:);
        Z2 = N(3,:);
        plot3(X2,Y2,Z2,'b-');
        hold on
        X1 = M(1,:);
        Y1 = M(2,:);
        Z1 = M(3,:);
        plot3(X1,Y1,Z1,'r-');
       
   end
   pause(0.1) 
   hold off
end
