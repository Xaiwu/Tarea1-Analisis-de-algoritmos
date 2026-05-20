/** uhr: generic time performance tester
 * Author: LELE
 *
 * Things to set up:
 * 0. Includes: include all files to be tested,
 * 1. Time unit: in elapsed_time,
 * 2. What to write on time_data,
 * 3. Data type and distribution of RNG,
 * 4. Additive or multiplicative stepping,
 * 5. The experiments: in outer for loop. */

#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "../algoritmos/clasico.h"
#include "../algoritmos/hibrido.h"
#include "../algoritmos/matrix_utils.h"
#include "../algoritmos/strassen.h"
#include "utils.cpp"

// Include to be tested files here

int main(int argc, char* argv[]) {
    if (argc < 8) {
        std::cerr << "Uso: " << argv[0]
                  << " <csv> <runs> <low> <up> <CLASICO|STRASSEN|HIBRIDO> "
                     "<REALES|ENTEROS|IDENTIDAD|SPARSE> <umbral>"
                  << std::endl;
        return 1;
    }

    std::int64_t runs, lower, upper;
    validate_input(argc, argv, runs, lower, upper);

    runs = std::stoll(argv[2]);
    lower = std::stoll(argv[3]);
    upper = std::stoll(argv[4]);

    std::string alg_choice = argv[5];  // "CLASICO", "STRASSEN" o "HIBRIDO"
    std::string exp_choice = argv[6];  // "REALES", "ENTEROS", etc.
    int umbral = std::stoi(argv[7]);   // n0 para HIBRIDO

    std::ofstream time_data;
    time_data.open(argv[1]);
    time_data << "n,t_mean,t_stdev,t_Q0,t_Q1,t_Q2,t_Q3,t_Q4" << std::endl;

    std::int64_t n, i, executed_runs = 0;
    std::int64_t total_runs =
        runs * (floor(log(upper / double(lower)) / log(2)) + 1);

    std::vector<double> times(runs);
    std::vector<double> q;

    std::cerr << "\033[0;36mRunning tests...\033[0m" << alg_choice << " ["
              << exp_choice << "]\033[0m" << std::endl;

    for (n = lower; n <= upper; n *= 2) {
        double mean_time = 0;

        // Generar las matrices FUERA del bucle de tiempo para no ensuciar la
        // medición
        Matriz A = crear_matriz(n);
        Matriz B = crear_matriz(n);
        preparar_experimento(exp_choice, A, B);

        for (i = 0; i < runs; i++) {
            display_progress(++executed_runs, total_runs);

            //  INICIO DE MEDICIÓN
            auto begin_time = std::chrono::high_resolution_clock::now();

            Matriz C;
            if (alg_choice == "CLASICO") {
                C = multiplicacion_clasica(A, B);
            } else if (alg_choice == "STRASSEN")
                C = multiplicacion_strassen(A, B);
            else {
                C = multiplicacion_hibrida(A, B, umbral);
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            // FIN DE MEDICIÓN

            std::chrono::duration<double, std::nano> elapsed =
                end_time - begin_time;
            times[i] = elapsed.count();
            mean_time += times[i];
        }

        //  Cálculos estadísticos
        mean_time /= runs;
        double time_stdev = 0;
        for (i = 0; i < runs; i++) {
            double dev = times[i] - mean_time;
            time_stdev += dev * dev;
        }
        time_stdev = std::sqrt(time_stdev / (runs - 1));

        quartiles(times, q);

        // Escribir al CSV
        time_data << n << "," << mean_time << "," << time_stdev << ",";
        time_data << q[0] << "," << q[1] << "," << q[2] << "," << q[3] << ","
                  << q[4] << std::endl;
    }

    std::cerr << "\033[1;32mDone!\033[0m" << std::endl;
    time_data.close();
    return 0;
}