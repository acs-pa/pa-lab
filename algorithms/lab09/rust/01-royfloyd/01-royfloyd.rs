// SPDX-License-Identifier: BSD-3-Clause

use std::fs::File;
use std::io::{BufRead, BufReader, Write};

#[derive(Default)]
struct Task {
    // n = numar de noduri
    n: i32,

    // w[x][y] = costul muchiei de la x la y: (x, y, w[x][y])
    // (w[x][y] = 0 - muchia lipseste)
    //
    // In aceasta problema, costurile sunt strict pozitive.
    w: Vec<Vec<i32>>,
}

impl Task {
    const NMAX: usize = 105;

    pub fn solve(&mut self) {
        self.read_input();
        let result = self.compute();
        self.write_output(&result);
    }

    fn read_input(&mut self) {
        let fin = File::open("in").expect("in");
        let reader = BufReader::new(fin);
        let mut all_tokens: Vec<i32> = Vec::new();
        for line in reader.lines() {
            let line = line.unwrap();
            for tok in line.split_whitespace() {
                all_tokens.push(tok.parse().unwrap());
            }
        }
        self.n = all_tokens[0];
        self.w = vec![vec![0; (self.n + 1) as usize]; (self.n + 1) as usize];
        let mut idx = 1;
        for x in 1..=self.n {
            for y in 1..=self.n {
                self.w[x as usize][y as usize] = all_tokens[idx];
                idx += 1;
            }
        }
    }

    fn compute(&self) -> Vec<Vec<i32>> {
        return self.royfloyd();
    }

    fn royfloyd(&self) -> Vec<Vec<i32>> {
        let mut d = vec![vec![0i32; (self.n + 1) as usize]; (self.n + 1) as usize];

        // Initializez matricea d folosind matricea w.
        for i in 1..=self.n {
            for j in 1..=self.n {
                d[i as usize][j as usize] = self.w[i as usize][j as usize];
            }
        }

        // Aplic Roy-Floyd:
        for k in 1..=self.n {
            // Fixez nodul intermediar, k.
            for i in 1..=self.n {
                for j in 1..=self.n {
                    if i == j {
                        continue;
                    }

                    // Daca nu exista drum de la i la k sau de la k la j, sarim peste.
                    if d[i as usize][k as usize] == 0 || d[k as usize][j as usize] == 0 {
                        continue;
                    }

                    // Fixez cele doua capete ale drumului pe care le updatez (i, j).
                    // Daca nu am drum sau daca obtin un cost mai mic intre i, j, updatez.
                    if d[i as usize][j as usize] == 0
                        || d[i as usize][k as usize] + d[k as usize][j as usize] < d[i as usize][j as usize]
                    {
                        d[i as usize][j as usize] =
                            d[i as usize][k as usize] + d[k as usize][j as usize];
                    }
                }
            }
        }

        return d;
    }

    fn write_output(&self, d: &[Vec<i32>]) {
        let mut fout = File::create("out").expect("out");
        for x in 1..=self.n {
            for y in 1..=self.n {
                write!(fout, "{} ", d[x as usize][y as usize]).unwrap();
            }
            writeln!(fout).unwrap();
        }
    }
}

// [ATENTIE] NU modifica functia main!
fn main() {
    let mut task = Box::new(Task::default());
    task.solve();
}
