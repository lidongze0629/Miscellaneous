def parse_log(fnum, log_path, total_vertex_num, L, mode):
    total_datasets = [None] * fnum
    total_labels = [None] * fnum
    
    t_data = [None] * fnum
    t_label = [None] * fnum
    v_data = [None] * fnum
    v_label = [None] * fnum

    log_file = open(log_path, 'r')
    lines = log_file.readlines()
    for line in lines:
        if line.find('TrainLog') != -1:
            fid, running_time, feature_vector = parse_log_data(line, total_vertex_num, L)
            if total_datasets[fid] == None:
                total_datasets[fid] = []
                total_labels[fid] = []
            total_datasets[fid].append(feature_vector)
            total_labels[fid].append(running_time)
    log_file.close()

def parse_log_data(line, total_vertex_num, L):
    
