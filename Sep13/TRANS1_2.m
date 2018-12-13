function X2 = TRANS1_2(X,theta2)
%convert s2 to s1
P12 = [cos(theta2),-sin(theta2),0;0,0,-1;sin(theta2),cos(theta2),0];
X2 = P12*X.'+[0,8,0].';
X2 = X2.';
end