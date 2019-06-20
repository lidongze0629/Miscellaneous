from parse import parse_log
import sys


if __name__ == '__main__':
    if len(sys.argv) != 5:
        print("Usage: python3 main.py <log_path> <fnum> <total_vertex_num> <L>")
        sys.exit()

    log_path = sys.argv[1]
    fnum = int(sys.argv[2])
    total_vertex_num = int(sys.argv[3])
    L = int(sys.argv[4])
    
    print("--------------- user params -----------------")
    print("L: " + str(L))
    print("fnum: " + str(fnum))
    print("total_vertex_num:" + str(total_vertex_num))
    print("log_path: " + log_path)

    print("--------------- parse log -------------------")
    # which t means train, v means validate
    t_data, t_label, v_data, v_label = parse_log(fnum, log_path, total_vertex_num, L, "random")
