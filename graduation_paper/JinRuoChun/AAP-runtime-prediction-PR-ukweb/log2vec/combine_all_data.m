clc;
clear all;
data_name = 'pr-ukweb-frag-192-data';
log_data_folder = 'D:\research\AAP\runTimePrediction\pagerank\ukweb\log2vec\192';
fileFolder=fullfile(log_data_folder);
dirOutput=dir(fullfile(fileFolder,'*'));
len = length(dirOutput);
disp(len);

total_feature_num = 0;
for i = 1:len

   if(length(dirOutput(i).name) < 4)
   continue;
   end
   
   cur_file_name = dirOutput(i).name;
   cur_file_path = [log_data_folder,'\',cur_file_name];
   load(cur_file_path);
   total_feature_num = total_feature_num + length(true_run_time);
   
end

time_span_all = zeros(total_feature_num,1);
[line col] = size(feature);
feature_all = zeros(total_feature_num,col);

start_p = 1;

for i = 1:len

   if(length(dirOutput(i).name) < 4)
   continue;
   end
   
   cur_file_name = dirOutput(i).name;
   cur_file_path = [log_data_folder,'\',cur_file_name];
   load(cur_file_path);
   cur_feature_num = length(true_run_time);
   time_span_all(start_p:cur_feature_num+start_p-1,1) = true_run_time;
    feature_all(start_p:cur_feature_num+start_p-1,:) = feature;
   start_p = start_p + cur_feature_num;
   
end

save(data_name,'time_span_all','feature_all');

