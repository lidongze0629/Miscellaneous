clc;
clear all;
% load('pr-friendster-frag-64-data.mat');

data = load('pr-ukweb-frag-64-data');
running_time_orinigal = data.time_span_all;
f_vector_original = data.feature_all;


[ Train_X,Train_Y,Test_X,Test_Y ] = Train_Test_Split( f_vector_original,running_time_orinigal,0.1 );



nTree = 10;
% train_data = X(:,1:end-1);train_label = X(:,end); test_data = T(:,1:end-1);
tic;
t1 = toc;
Factor = TreeBagger(nTree, Train_X, Train_Y,'Method','regression');
t2 = toc;
disp('train time:');
disp((t2-t1)*1000);

t3 = toc;
[Predict_label,Scores] = predict(Factor, Test_X);
t4 = toc;

disp('ave predict time:');
disp((t4-t3)*1000/length(Test_Y));

total_diff = 0;
baseline_total_diff=0;
diff_num = 0;
mean_test_time = 0;
mean_base = mean(Test_Y);
% mean_run_time = 0;
for i = 1:length(Scores)
    if(i>1)
    mean_base = mean(Test_Y(1:i-1));
    end
   if(Scores(i) < 6)
       total_diff = total_diff + ((Predict_label(i) - Test_Y(i))/ Test_Y(i))^2;
       diff_num = diff_num + 1;
       baseline_total_diff = baseline_total_diff +((mean_base - Test_Y(i))/ Test_Y(i))^2;
  
   end
    
    
end

% disp(length(Train_Y));
% disp(diff_num);

disp('MSRE');
disp(total_diff/diff_num);

disp('MSRE baseline');
disp(baseline_total_diff/diff_num);


ave_diff = total_diff / diff_num;
mean_test_time = mean_test_time / diff_num;

MAE = mean(abs(Predict_label - Test_Y(:,end)));

diff = abs(Predict_label - Test_Y(:,end));
% disp(mean_test_time);
% disp(ave_diff);