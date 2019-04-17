clc;
clear;
ini_4_letters = 'page';
feature_scale = 6;
% feature_num = 3;
related_start_position = 29;
related_end_positioin = 32;
log_data_folder = 'D:\research\AAP\runTimePrediction\pagerank\ukweb\tianhe-log\192';
fileFolder=fullfile(log_data_folder);
dirOutput=dir(fullfile(fileFolder,'*'));
len = length(dirOutput);
disp(len);
for i = 1:len

   if(length(dirOutput(i).name) < 4)
   continue;
   end
   if strcmp(dirOutput(i).name(1:4),ini_4_letters)
       cur_file_name = dirOutput(i).name;
       cur_file_path = [log_data_folder,'\',cur_file_name];
   end
   disp(i);
   disp(cur_file_name);
   ffid = fopen(cur_file_path,'r');

   j = 1;
   while( feof(ffid) == 0   )
     
       tline{j,1} = fgetl(ffid);
       j = j+1;
   end
   
   file_line_num = length(tline);
   related_file_line = 1;
   for j = 1:file_line_num
      if(length( tline{j,1}) < related_start_position)
         continue; 
      end
    if strcmp(tline{j,1}(related_start_position:related_end_positioin),ini_4_letters)
      
        related_lines{related_file_line,1} = tline{j,1};
        related_file_line = related_file_line + 1;
    end
   end
   
   max_g_id = 0;
   
   interval = ceil(max_g_id / feature_scale);
   
   feature = zeros(length(related_lines),feature_scale);
   true_run_time = zeros(length(related_lines),1);
   
    for k = 1:length(related_lines)
 
       cur_line = related_lines{k,:};
       [ run_time,total_v_num,innner_v_num,ov_num,f_id,frag_enum ] = get_pr_feature_from_line( cur_line );
    true_run_time(k,1) = run_time;
       feature(k,end) = total_v_num;
       feature(k,end-1) = innner_v_num;
       feature(k,end-2) = ov_num;
       feature(k,end-3) = frag_enum;
       feature(k,end-4) = innner_v_num / total_v_num;
       feature(k,end-5) = frag_enum / total_v_num;
         

       
    end
   true_run_time = true_run_time * 1000;
%     disp('temp');
      save_file_name_cell = regexp(cur_file_name, 'INFO.', 'split');
   save_file_name = [save_file_name_cell{1,2},'-log.mat'];
   save(save_file_name,'true_run_time','feature'); 

    
end


