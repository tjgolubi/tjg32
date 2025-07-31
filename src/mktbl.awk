/^Compiled with/ {
  optimize = $3;
}

/^Crc[0-9]+::Update time:/ {
  if (match($1, /[0-9]+/))
    num = substr($1, RSTART, RLENGTH);
  else
    num = $1;
  dt = $3;
  name = $7;
  names[num] = name;
  table[num][optimize] = dt;
}

END {
  PROCINFO["sorted_in"] = "@ind_num_asc";
  for (num in table) {
    printf "| %-14s", "Algorithm";
    for (opt in table[num])
      printf " |  %3s  ", opt;
    printf " |\n|:---------------";
    for (opt in table[num])
      printf "|-------:";
    printf "|\n";
    break;
  }

  for (num in table) {
    printf "| %-14s", names[num];
    for (opt in table[num])
      printf " |%7s", table[num][opt];
    printf " |\n";
  }
}
