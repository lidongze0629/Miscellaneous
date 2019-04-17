function [ run_time,total_v_num,innner_v_num,ov_num,f_id,frag_enum ] = get_sssp_feature_from_line( cur_line )


       first_split = regexp(cur_line, '] ', 'split');
       
       second_split = regexp(first_split{1,2}, ';', 'split');
       
       run_time = str2double(second_split{1,1});
       total_v_num = str2double(second_split{1,2});
       innner_v_num = str2double(second_split{1,3});
       ov_num = str2double(second_split{1,4});
       f_id = str2double(second_split{1,5});
       frag_enum = str2double(second_split{1,6});


end

