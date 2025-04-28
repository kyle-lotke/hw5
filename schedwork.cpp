#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool set_shifts(const AvailabilityMatrix& AV_matrix,
    size_t daily_shifts,
    size_t max_shifts,
    size_t curr_day,
    size_t shift,
    DailySchedule& schedule,
    map<Worker_T, int>& shifts_left);

// Add your implementation of schedule() and other helper functions here

bool set_shifts(const AvailabilityMatrix& AV_matrix,
    size_t daily_shifts,
    size_t max_shifts,
    size_t curr_day,
    size_t shift,
    DailySchedule& schedule,
    map<Worker_T, int>& shifts_left)
{
    
    if (curr_day == AV_matrix.size()) { // base case: all days are scheduled
        return true;
    }

    //  assing each worker to the current shift
    for (Worker_T worker_id = 0; worker_id < (Worker_T)AV_matrix[curr_day].size(); ++worker_id) {
        if (AV_matrix[curr_day][worker_id] && shifts_left[worker_id] > 0) {

            schedule[curr_day][shift] = worker_id;
            shifts_left[worker_id]--;

            size_t next_day;
            if (shift + 1 == daily_shifts) {
                next_day = curr_day + 1;
            }
            else {
                next_day = curr_day;
            }

            size_t next_shift;
            if (shift + 1 == daily_shifts) {
                next_shift = 0;
            }
            else {
                next_shift = shift + 1;
            }

            if (set_shifts(AV_matrix, daily_shifts, max_shifts, next_day, next_shift, schedule, shifts_left)) {
                return true;
            }

            schedule[curr_day][shift] = INVALID_ID;
            shifts_left[worker_id]++;
        }
    }

    // can't find valid assignment
    return false;
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    const size_t days = avail.size();
    const size_t workers = avail[0].size();
    sched.resize(days);                                
    for (size_t day = 0; day < days; day++) {
      sched[day].resize(dailyNeed, INVALID_ID);         
    }
    map<Worker_T, int> shifts_left;
    for (Worker_T worker = 0; worker < workers; worker++){
      shifts_left[worker] = maxShifts;
    }

    return set_shifts(avail,dailyNeed,maxShifts,0,0,sched,shifts_left);
}

