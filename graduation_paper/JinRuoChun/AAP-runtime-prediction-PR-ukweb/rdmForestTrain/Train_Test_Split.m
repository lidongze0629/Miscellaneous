function [ Train_X,Train_Y,Test_X,Test_Y ] = Train_Test_Split( original_feature,original_label,train_percentage )
%TRAIN_TEST_SPLIT Summary of this function goes here
%   Detailed explanation goes here

total_feature_num = length(original_label);

randIndex = randperm(total_feature_num);

train_num = floor(train_percentage * total_feature_num);
test_num = total_feature_num - train_num;

[line,col] = size(original_feature);

Train_Y = zeros(train_num,1);
Test_Y = zeros(test_num,1);

Train_X = zeros(train_num,col);
Test_X = zeros(test_num,col);

train_p = 1;
test_p = 1;

for i = 1:total_feature_num
    cur_idx = randIndex(i);
   if(i > train_num)%test
       
   Test_X(test_p,:) = original_feature(cur_idx,:);
   Test_Y(test_p) = original_label(cur_idx);
   test_p = test_p + 1;
       
   else%train
   Train_X(train_p,:) = original_feature(cur_idx,:);
   Train_Y(train_p) = original_label(cur_idx);
   train_p = train_p + 1;
   end
    
    
end

end

