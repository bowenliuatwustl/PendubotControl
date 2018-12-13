function [  ] = ReplayScope( theta1, theta2 )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
A = [0 0 0];
B = [0 0 -1];
C = [0 6 -1];
D = [0 6 0];
E = [0 8 0];
F = [0 0 0];
G = [0 12 0];


      
        
        A1 = TRANS0_1(A,theta1);
        B1 = TRANS0_1(B,theta1);
        C1 = TRANS0_1(C,theta1);
        D1 = TRANS0_1(D,theta1);
        E1 = TRANS0_1(E,theta1);
        
        F2 = TRANS1_2(F,theta2);
        G2 = TRANS1_2(G,theta2);
        F1 = TRANS0_1(F2,theta1);
        G1 = TRANS0_1(G2,theta1);
        
            M = [A1.',B1.',C1.',D1.',E1.'];
            X1 = M(1,:);
            Y1 = M(2,:);
            Z1 = M(3,:);
            
            N = [F1.',G1.'];
            X2 = N(1,:);
            Y2 = N(2,:);
            Z2 = N(3,:);
            
            plot3(X1,Y1,Z1,'r-');
            plot3(X2,Y2,Z2,'b-');
            axis([-15 15 -15 15 -15 15]);
    
